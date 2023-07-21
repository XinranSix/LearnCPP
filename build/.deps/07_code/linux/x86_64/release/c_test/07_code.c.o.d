{
    files = {
        "c_test/07_code.c"
    },
    depfiles_gcc = "07_code.o: c_test/07_code.c\
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