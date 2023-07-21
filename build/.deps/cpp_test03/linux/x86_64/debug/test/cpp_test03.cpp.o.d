{
    depfiles_gcc = "cpp_test03.o: test/cpp_test03.cpp\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-std=c++20",
            "-Iinclude",
            "-isystem",
            "/home/yaojie/.xmake/packages/f/fmt/10.0.0/cf4a2efd8ed34f738dfde8eaa4fb9660/include",
            "-isystem",
            "/home/yaojie/.xmake/packages/g/gtest/1.12.1/77b9096bc4b34d9282f672d36b015ba9/include",
            "-isystem",
            "/home/yaojie/.xmake/packages/b/boost/1.81.0/9a76068f70604ea18becd4a3064bdac1/include",
            "-isystem",
            "/home/yaojie/.xmake/packages/b/bzip2/1.0.8/8db6bd46210f4711a452b7767b44748c/include",
            "-isystem",
            "/home/yaojie/.xmake/packages/f/ftxui/v3.0.0/c4565ddf60a74478a0fa81d2d54d4767/include"
        }
    },
    files = {
        "test/cpp_test03.cpp"
    }
}