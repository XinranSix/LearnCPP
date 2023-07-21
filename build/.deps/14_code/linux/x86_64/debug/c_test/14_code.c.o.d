{
    depfiles_gcc = "14_code.o: c_test/14_code.c\
",
    files = {
        "c_test/14_code.c"
    },
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