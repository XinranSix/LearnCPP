{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-Iinclude",
            "-DNDEBUG"
        }
    },
    depfiles_gcc = "11_code.o: c_test/11_code.c\
",
    files = {
        "c_test/11_code.c"
    }
}