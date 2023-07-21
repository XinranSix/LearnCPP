{
    files = {
        "c_test/12_code.c"
    },
    depfiles_gcc = "12_code.o: c_test/12_code.c\
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