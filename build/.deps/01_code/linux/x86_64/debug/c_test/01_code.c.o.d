{
    files = {
        "c_test/01_code.c"
    },
    depfiles_gcc = "01_code.o: c_test/01_code.c\
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