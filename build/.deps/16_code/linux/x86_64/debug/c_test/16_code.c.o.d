{
    depfiles_gcc = "16_code.o: c_test/16_code.c\
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
        "c_test/16_code.c"
    }
}