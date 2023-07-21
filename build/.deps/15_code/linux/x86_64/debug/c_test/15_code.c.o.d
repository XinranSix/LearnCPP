{
    depfiles_gcc = "15_code.o: c_test/15_code.c\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-Iinclude"
        }
    },
    files = {
        "c_test/15_code.c"
    }
}