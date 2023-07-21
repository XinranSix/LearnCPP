{
    files = {
        "c_test/17_code.c"
    },
    depfiles_gcc = "17_code.o: c_test/17_code.c\
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