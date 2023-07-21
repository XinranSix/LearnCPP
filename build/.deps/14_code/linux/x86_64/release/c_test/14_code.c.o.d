{
    files = {
        "c_test/14_code.c"
    },
    depfiles_gcc = "14_code.o: c_test/14_code.c\
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