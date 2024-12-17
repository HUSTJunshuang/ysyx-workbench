#include <common.h>
#include <elf.h>

#ifndef CONFIG_TARGET_AM

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
    MUXDEF(CONFIG_ISA64, Elf64_Ehdr, Elf32_Ehdr) Ehdr;
    icb.call_depth = 0;
    icb.elf_fp = fopen(elf_file, "rb");
    Assert(icb.elf_fp, "Can not open '%s'", elf_file);
    // read ELFN_Ehdr
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
    printf("section num = %ld\n", section_num);
    // MUXDEF(CONFIG_ISA64, Elf64_Shdr, Elf32_Shdr) Shdr[section_num];
    for (int i = 1; i < section_num; ++i) {
        fseek(icb.elf_fp, Ehdr.e_shoff + sizeof(shdr) * i, SEEK_SET);
        Assert(fread(&shdr, sizeof(shdr), 1, icb.elf_fp) == 1, "Read Elf%d_Shdr[%d] failed", XLEN, i);
        if (shdr.sh_type == SHT_SYMTAB) {
            symtab_shdr = shdr;
        }
        if (shdr.sh_type == SHT_STRTAB) {
            strtab_shdr = shdr;
        }
    }
    printf("symbol num = %ld\n", symtab_shdr.sh_size / sym_size);
    printf("strtab offset = %ld\n", strtab_shdr.sh_offset);
}

#if (__GUEST_ISA__ == riscv32 || __GUEST_ISA__ == riscv64)
void check_invoke(uint32_t inst, vaddr_t pc, vaddr_t dnpc, int ret) {
    int rd = BITS(inst, 11, 7);
    int rs1 = BITS(inst, 19, 15);
    // process symtab
    uint64_t sym_num = symtab_shdr.sh_size / sym_size;
    // char *call_func = NULL, *ret_func = NULL;
    MUXDEF(CONFIG_ISA64, Elf64_Sym, Elf32_Sym) sym;
    for (int i = 0; i < sym_num; ++i) {
        // read sym
        fseek(icb.elf_fp, symtab_shdr.sh_offset + sym_size * i, SEEK_SET);
        Assert(fread(&sym, sizeof(sym), 1, icb.elf_fp), "Read Elf%d_Sym[%d] failed", XLEN, i);
        if (sym.st_info != STT_FUNC)    continue;
        // vaddr_t func_start = sym.st_value;
        // vaddr_t func_end = func_start + sym.st_size;
        // if (pc >= func_start && pc < func_end) {
        //     call_func = sym.st_name;
        // }
        // if (dnpc >= func_start && dnpc < func_end) {
        //     ret_func = (char *)sym.st_name;
        // }
    }
    if (rd == 1 || rd == 5) {
        // printf(FMT_WORD ": %*scall [%s@" FMT_WORD "]\n", pc, icb.call_depth * 2, "", call_func, dnpc);
        ++icb.call_depth;
    }
    if (ret == 1 && rd == 0 && rs1 == 1) {
        --icb.call_depth;
        // printf(FMT_WORD ": %*sret  [%s]\n", pc, icb.call_depth * 2, "", ret_func);
    }
}
#endif

#endif
