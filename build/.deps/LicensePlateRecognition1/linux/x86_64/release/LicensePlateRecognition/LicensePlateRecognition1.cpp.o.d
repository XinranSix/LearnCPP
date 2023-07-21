{
    files = {
        "LicensePlateRecognition/LicensePlateRecognition1.cpp"
    },
    depfiles_gcc = "LicensePlateRecognition1.o:  LicensePlateRecognition/LicensePlateRecognition1.cpp include/ocr.h  include/base/base.h include/base/http.h include/base/base64.h  include/base/utils.h\
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
            "/home/yaojie/.xmake/packages/j/jsoncpp/1.9.5/6a59121558c24c01a73b20670010be3a/include",
            "-DNDEBUG"
        }
    }
}