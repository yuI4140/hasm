const char *INSTRUCTIONS[205] = {
    "syscall", "call", "jmp", "je", "jne", "jz", "jnz", "ja", "jae", "jb", "jbe", "jl", "jle",
    "jg", "jge", "jo", "jno", "js", "jns", "jc", "jnc", "jpe", "jpo", "loop", "loope", "loopne",
    "loopz", "loopnz", "ret", "retf", "add", "sub", "mul", "imul", "div", "idiv", "inc", "dec",
    "neg", "not", "and", "or", "xor", "shl", "sal", "shr", "sar", "rol", "ror", "rcl", "rcr",
    "mov", "push", "pop", "lea", "xchg", "xadd", "cmpxchg", "movzx", "movsx", "movsb", "movsw",
    "movsd", "movd", "movq", "xmm", "mmx", "pusha", "popa", "pushad", "popad", "pushf", "popf",
    "enter", "leave", "pushfd", "popfd", "movsp", "movbp", "movsq", "lodsb", "lodsw", "lodsd",
    "stosb", "stosw", "stosd", "scasb", "scasw", "scasd", "seta", "setae", "setb", "setbe", "sete",
    "setne", "setg", "setge", "setl", "setle", "seto", "setno", "sets", "setns", "setz", "setnz",
    "fadd", "fsub", "fmul", "fdiv", "fsqrt", "fcomp", "fcompp", "fabs", "fchs", "fincstp",
    "fdecstp", "fld", "fst", "fstp", "fild", "fist", "fistp", "fisttp", "fildll", "fistll",
    "fistpll", "fld1", "fldl2t", "fldl2e", "fldpi", "fldlg2", "fldln2", "fldz", "fpatan", "fprem",
    "fprem1", "fptan", "frndint", "fscale", "fsin", "fcos", "fsincos", "fsinh", "fcosh", "ftanh",
    "fatan", "fatan2", "fxch", "fcom", "fcomi", "fcomip", "fucom", "fucomi", "fucomip", "ftst",
    "fucompp", "movaps", "movups", "movapd", "movupd", "movdqa", "movdqu", "movq", "movss",
    "movsd", "movlhps", "movhlps", "movlps", "movhps", "movlps", "movq2dq", "movdq2q", "movntdq",
    "movntdqa", "movnti", "movntpd", "movntps", "movntq", "nop", "int", "xabort", "xbegin", "xend",
    "xtest", "ud2", "hlt", "cli", "sti", "rdtsc", "cpuid", "pause", "lfence", "mfence", "sfence",
    "xgetbv", "xsetbv", "crc32", "bsf", "bsr", "btr", "bt", "btc", "bts", "lzcnt", "popcnt",
};

const char *REGISTERS[48] = {
    "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp", "r8", "r9", "r10", "r11", "r12", "r13",
    "r14", "r15", "rip", "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7", "xmm8",
    "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15", "mm0", "mm1", "mm2", "mm3",
    "mm4", "mm5", "mm6", "mm7", "cs", "ds", "es", "fs", "gs", "ss", "eflags",
};

const struct {
    const char *name;
    int value;
} SYSCALLS[13] = {
    {"read", 0},
    {"write", 1},
    {"open", 2},
    {"close", 3},
    {"stat", 4},
    {"fstat", 5},
    {"lstat", 6},
    {"poll", 7},
    {"lseek", 8},
    {"mmap", 9},
    {"mprotect", 10},
    {"munmap", 11},
    {"brk", 12},
};
