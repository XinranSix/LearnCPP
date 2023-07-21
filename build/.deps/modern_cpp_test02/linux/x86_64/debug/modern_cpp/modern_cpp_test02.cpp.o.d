{
    files = {
        "modern_cpp/modern_cpp_test02.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-std=c++20",
            "-Iinclude",
            "-isystem",
            "/home/yaojie/.xmake/packages/f/fmt/10.0.0/cf4a2efd8ed34f738dfde8eaa4fb9660/include"
        }
    },
    depfiles_gcc = "modern_cpp_test02.o: modern_cpp/modern_cpp_test02.cpp\
"
}