{
    files = {
        "modern_cpp/modern_cpp_test01.cpp"
    },
    depfiles_gcc = "modern_cpp_test01.o: modern_cpp/modern_cpp_test01.cpp include/ocr.h  include/base/base.h include/base/http.h include/base/base64.h  include/base/utils.h\
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
            "/home/yaojie/.xmake/packages/j/jsoncpp/1.9.5/6a59121558c24c01a73b20670010be3a/include"
        }
    }
}