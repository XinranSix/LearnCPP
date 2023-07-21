{
    files = {
        "c_test/08_code.c"
    },
    depfiles_gcc = "08_code.o: c_test/08_code.c\
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