{
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-g",
            "-O0",
            "-std=c++20",
            "-Iinclude",
            "-isystem",
            "/home/yaojie/.xmake/packages/j/jsoncpp/1.9.5/6a59121558c24c01a73b20670010be3a/include"
        }
    },
    depfiles_gcc = "LicensePlateRecognition.o:  LicensePlateRecognition/LicensePlateRecognition.cpp include/ocr.h  include/base/base.h include/base/http.h include/base/base64.h  include/base/utils.h\
",
    files = {
        "LicensePlateRecognition/LicensePlateRecognition.cpp"
    }
}