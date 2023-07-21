{
    files = {
        "c_test/04_code.c"
    },
    depfiles_gcc = "04_code.o: c_test/04_code.c\
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