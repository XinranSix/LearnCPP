{
    files = {
        "c_test/17_code.c"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-Iinclude"
        }
    },
    depfiles_gcc = "17_code.o: c_test/17_code.c\
"
}