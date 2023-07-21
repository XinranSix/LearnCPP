{
    depfiles_gcc = "13_code.o: c_test/13_code.c\
",
    files = {
        "c_test/13_code.c"
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