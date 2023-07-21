{
    files = {
        "c_test/13_code.c"
    },
    depfiles_gcc = "13_code.o: c_test/13_code.c\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-Iinclude",
            "-DNDEBUG"
        }
    }
}