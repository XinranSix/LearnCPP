{
    files = {
        "c_test/09_code.c"
    },
    depfiles_gcc = "09_code.o: c_test/09_code.c\
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