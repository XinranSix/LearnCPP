{
    files = {
        "sort/countingSort.cpp"
    },
    depfiles_gcc = "countingSort.o: sort/countingSort.cpp\
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
            "/home/yaojie/.xmake/packages/g/gtest/1.12.1/77b9096bc4b34d9282f672d36b015ba9/include",
            "-DNDEBUG"
        }
    }
}