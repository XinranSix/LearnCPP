{
    files = {
        "c_test/05_code.c"
    },
    depfiles_gcc = "05_code.o: c_test/05_code.c\
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