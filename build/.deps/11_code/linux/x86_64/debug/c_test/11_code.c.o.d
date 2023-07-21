{
    files = {
        "c_test/11_code.c"
    },
    depfiles_gcc = "11_code.o: c_test/11_code.c\
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