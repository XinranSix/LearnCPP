{
    files = {
        "c_test/12_code.c"
    },
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
    depfiles_gcc = "12_code.o: c_test/12_code.c\
"
}