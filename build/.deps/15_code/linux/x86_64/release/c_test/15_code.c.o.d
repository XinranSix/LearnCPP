{
    files = {
        "c_test/15_code.c"
    },
    depfiles_gcc = "15_code.o: c_test/15_code.c\
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