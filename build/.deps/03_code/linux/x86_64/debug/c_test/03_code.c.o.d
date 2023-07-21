{
    files = {
        "c_test/03_code.c"
    },
    depfiles_gcc = "03_code.o: c_test/03_code.c\
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