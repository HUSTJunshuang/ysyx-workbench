#include <common.h>
#include <elf.h>
#include <string.h>

#ifndef CONFIG_TARGET_AM

#define MAX_SEC_NAME_LEN 32
#define MAX_FUNC_NAME_LEN 256

// ftrace, invocation control block
typedef struct {
  int call_depth;
  FILE *elf_fp;
} ICB;

static ICB icb;
static MUXDEF(CONFIG_ISA64, Elf64_Shdr, Elf32_Shdr) symtab_shdr;
static MUXDEF(CONFIG_ISA64, Elf64_Shdr, Elf32_Shdr) strtab_shdr;

const size_t sym_size = sizeof(MUXDEF(CONFIG_ISA64, Elf64_Sym, Elf32_Sym));

void init_icb(const char *elf_file) {
    icb.call_depth = 0;
    icb.elf_fp = fopen(elf_file, "rb");
    // Assert(icb.elf_fp != NULL, "Can not open '%s'", elf_file);
    if (icb.elf_fp == NULL) {
        Log("Failed to open the elf file '%s'", elf_file);
        return ;
    }
    // read ELFN_Ehdr
    MUXDEF(CONFIG_ISA64, Elf64_Ehdr, Elf32_Ehdr) Ehdr;
    Assert(fread(&Ehdr, sizeof(Ehdr), 1, icb.elf_fp) == 1, "Read Elf%d_Ehdr failed", XLEN);
    // check magic number and hardware architecture
    Assert(Ehdr.e_ident[0] == 0x7f, "'%s' is not a elf file, with EI_MAG0 = %x, expected 0x7f", elf_file, Ehdr.e_ident[0]);
    Assert(Ehdr.e_ident[1] == 'E', "'%s' is not a elf file, with EI_MAG1 = '%c', expected 'E'", elf_file, Ehdr.e_ident[1]);
    Assert(Ehdr.e_ident[2] == 'L', "'%s' is not a elf file, with EI_MAG2 = '%c', expected 'L'", elf_file, Ehdr.e_ident[2]);
    Assert(Ehdr.e_ident[3] == 'F', "'%s' is not a elf file, with EI_MAG3 = '%c', expected 'F'", elf_file, Ehdr.e_ident[3]);
    Assert(Ehdr.e_ident[4] != ELFCLASSNONE, "EI_CLASS invalid, with EI_CLASS = ELFCLASSNONE");
    int arch = (Ehdr.e_ident[4] == ELFCLASS32) ? 32 : 
                (Ehdr.e_ident[4] == ELFCLASS64) ? 64 : 0;
    Assert(Ehdr.e_ident[4] == MUXDEF(CONFIG_ISA64, ELFCLASS64, ELFCLASS32), "Architecture dose not match, with EI_CLASS = %d-bit, expected %d-bit", arch, XLEN);
    // check section header table
    Assert(Ehdr.e_shoff, "'%s' has no section header table", elf_file);
    uint64_t section_num = Ehdr.e_shnum;
    MUXDEF(CONFIG_ISA64, Elf64_Shdr, Elf32_Shdr) shdr;
    fseek(icb.elf_fp, Ehdr.e_shoff, SEEK_SET);
    Assert(fread(&shdr, sizeof(shdr), 1, icb.elf_fp) == 1, "Read Initial Elf%d_Shdr failed", XLEN);
    if (section_num == 0) {
        section_num = shdr.sh_size;
    }
    // read .shstrtab
    Assert(Ehdr.e_shstrndx != SHN_UNDEF, "'%s' has no shstrtab", elf_file);
    MUXDEF(CONFIG_ISA64, Elf64_Shdr, Elf32_Shdr) shstrtab_shdr;
    if (Ehdr.e_shstrndx != SHN_XINDEX) {
        fseek(icb.elf_fp, Ehdr.e_shoff + sizeof(shstrtab_shdr) * Ehdr.e_shstrndx, SEEK_SET);
    }
    else {
        fseek(icb.elf_fp, Ehdr.e_shoff + sizeof(shstrtab_shdr) * shdr.sh_link, SEEK_SET);
    }
    Assert(fread(&shstrtab_shdr, sizeof(shstrtab_shdr), 1, icb.elf_fp) == 1, "Read .shstrtab failed");
    // find .symtab and .strtab
    char sec_name[32];
    for (int i = 1; i < section_num; ++i) {
        fseek(icb.elf_fp, Ehdr.e_shoff + sizeof(shdr) * i, SEEK_SET);
        Assert(fread(&shdr, sizeof(shdr), 1, icb.elf_fp) == 1, "Read Elf%d_Shdr[%d] failed", XLEN, i);
        fseek(icb.elf_fp, shstrtab_shdr.sh_offset + shdr.sh_name, SEEK_SET);
        Assert(fgets(sec_name, MAX_SEC_NAME_LEN, icb.elf_fp), "Read Section Name[%d] failed", i);
        if (strcmp(sec_name, ".symtab") == 0) {
            symtab_shdr = shdr;
        }
        if (strcmp(sec_name, ".strtab") == 0) {
            strtab_shdr = shdr;
        }
    }
}

#if (__GUEST_ISA__ == riscv32 || __GUEST_ISA__ == riscv64)
void check_invoke(uint32_t inst, vaddr_t pc, vaddr_t dnpc, int ret) {
    if (icb.elf_fp == NULL) return ;
    int rd = BITS(inst, 11, 7);
    int rs1 = BITS(inst, 19, 15);
    // process symtab
    uint64_t sym_num = symtab_shdr.sh_size / sym_size;
    char call_func[MAX_FUNC_NAME_LEN], ret_func[MAX_FUNC_NAME_LEN];
    MUXDEF(CONFIG_ISA64, Elf64_Sym, Elf32_Sym) sym;
    for (int i = 0; i < sym_num; ++i) {
        // read sym
        fseek(icb.elf_fp, symtab_shdr.sh_offset + sym_size * i, SEEK_SET);
        Assert(fread(&sym, sizeof(sym), 1, icb.elf_fp), "Read Elf%d_Sym[%d] failed", XLEN, i);
        if (MUXDEF(CONFIG_ISA64, ELF64_ST_TYPE, ELF32_ST_TYPE)(sym.st_info) != STT_FUNC)    continue;
        vaddr_t func_start = sym.st_value;
        vaddr_t func_end = func_start + sym.st_size;
        if (pc >= func_start && pc < func_end) {
            fseek(icb.elf_fp, strtab_shdr.sh_offset + sym.st_name, SEEK_SET);
            Assert(fgets(ret_func, MAX_FUNC_NAME_LEN, icb.elf_fp), "Read call function name failed");
        }
        if (dnpc >= func_start && dnpc < func_end) {
            fseek(icb.elf_fp, strtab_shdr.sh_offset + sym.st_name, SEEK_SET);
            Assert(fgets(call_func, MAX_FUNC_NAME_LEN, icb.elf_fp), "Read ret function name failed");
        }
    }
    if (rd == 1 || rd == 5) {
        printf(FMT_WORD ": %*scall [%s@" FMT_WORD "]\n", pc, icb.call_depth * 2, "", call_func, dnpc);
        log_write(FMT_WORD ": %*scall [%s@" FMT_WORD "]\n", pc, icb.call_depth * 2, "", call_func, dnpc);
        ++icb.call_depth;
    }
    if (ret == 1 && rd == 0 && rs1 == 1) {
        --icb.call_depth;
        printf(FMT_WORD ": %*sret  [%s]\n", pc, icb.call_depth * 2, "", ret_func);
        log_write(FMT_WORD ": %*sret  [%s]\n", pc, icb.call_depth * 2, "", ret_func);
    }
}
#else
// TODO define architecture-specific function
#endif

#endif
