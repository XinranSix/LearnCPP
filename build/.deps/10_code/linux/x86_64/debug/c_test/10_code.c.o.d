{
    files = {
        "c_test/10_code.c"
    },
    depfiles_gcc = "10_code.o: c_test/10_code.c\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-Iinclude"
        }
    }
}