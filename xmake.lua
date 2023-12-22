add_rules("mode.debug", "mode.release")
set_languages("c++20")
add_cxflags("/utf-8")

-- add_includedirs("./include")

includes("./代码片段")
includes("./学习过程中写的代码")

if is_plat("windows") then
    add_requires("opencv")
    add_requires("opengl") 
    add_requires("libsdl") 
    add_requires("openscenegraph") 
    add_requires("glew") 
    add_requires("glad")
    add_requires("glfw")
    add_requires("glm")
    add_requires("assimp")
    add_requires("stb") -- 
end

if is_plat("linux") then
    add_requires("ncurses") -- 一个不支持 window 的 TUI 库
    add_requires("gnu-gsl") -- The GNU Scientific Library (GSL) is a numerical library for C and C++ programmers.
    add_requires("jemalloc") -- A general purpose malloc(3) implementation that emphasizes fragmentation avoidance and scalable concurrency support
end

-- 数据可视化
add_requires("matplotplusplus") -- A C++ Graphics Library for Data Visualization

-- 音视频
add_requires("ffmpeg")

-- 图形学 
add_requires("libigl") -- 各种图形学算法大合集
add_requires("cgal") --CGAL is a software project that provides easy access to efficient and reliable geometric algorithms in the form of a C++ library. 

-- 对标准库的拓展和补充
add_requires("boost", {configs = {all = true}}) 
add_requires("poco") 
add_requires("range-v3")  -- 范围库
add_requires("abseil") -- 补充标准库没有的常用功能

-- 工具
add_requires("fmt") -- 格式化输出库，巨好用，部分功能已被标准库吸收
add_requires("tbox") -- c 语言的一个工具库，Xmake 作者开发的
add_requires("cryptopp") -- 一套密码学程序库，使用了大量泛型编程技术，与 Boost 类似，几乎囊括了所有已知的公开密码学算法的实现
add_requires("snappy") -- A fast compressor/decompressor
add_requires("zeromq") -- High-performance, asynchronous messaging library
add_requires("boost_ut") --  UT: C++20 μ(micro)/Unit Testing Framework

-- 数学
add_requires("eigen") -- 一个线性代数库，还挺火的

-- 测试
add_requires("gtest") -- google test
add_requires("benchmark") -- 谷歌性能评估框架、

-- 反射与序列化
add_requires("magic_enum")  -- 枚举反射
add_requires("rttr") -- 反射库
-- MessagePack 高效易用的序列化和反序列化工具，可以跨语言交换数据
add_requires("msgpack-cxx") -- MessagePack implementation for C++
-- add_requires("msgpack-c") -- MessagePack implementation for C

-- 日志与文本解析
add_requires("spdlog") -- 一个日志库, 基于 fmt
add_requires("glog") -- 
add_requires("easyloggingpp") 

-- 数值计算
add_requires("gsl") -- C数学运算库

-- 其他库
add_requires("icu4c") -- C/C++ libraries for Unicode and globalization.
add_requires("libevent") -- 

-- 数据解析库
add_requires("tinyxml2") 
add_requires("yaml-cpp") 
add_requires("rapidjson") 
add_requires("jsoncpp") 
add_requires("pugixml") -- Light-weight, simple and fast XML parser for C++ with XPath support
add_requires("jsoncons") -- A C++, header-only library for constructing JSON and JSON-like data formats, with JSON Pointer, JSON Patch, JSONPath, JMESPath, CSV, MessagePack, CBOR, BSON, UBJSON

-- 数据序列化库
add_requires("protobuf-cpp") 

-- GUI 和 TUI
add_requires("wxwidgets") -- Cross-Platform C++ GUI Library

-- 命令行解析库
add_requires("gflags") 

