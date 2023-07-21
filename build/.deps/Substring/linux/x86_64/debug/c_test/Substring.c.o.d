{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-Iinclude"
        }
    },
    files = {
        "c_test/Substring.c"
    },
    depfiles_gcc = "Substring.o: c_test/Substring.c\
"
}