{
    files = {
        "modern_cpp/可变参数模板.cpp"
    },
    depfiles_gcc = "可变参数模板.o: modern_cpp/可变参数模板.cpp\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++20",
            "-Iinclude",
            "-isystem",
            "/home/yaojie/.xmake/packages/f/fmt/10.0.0/cf4a2efd8ed34f738dfde8eaa4fb9660/include",
            "-isystem",
            "/home/yaojie/.xmake/packages/j/jsoncpp/1.9.5/6a59121558c24c01a73b20670010be3a/include",
            "-DNDEBUG"
        }
    }
}