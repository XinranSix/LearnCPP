add_rules("mode.debug", "mode.release")
set_languages("c++20")

add_includedirs("include")

add_requires("fmt") -- fmt 库
add_requires("sqlite3") -- sqlite3 
add_requires("ftxui") -- ftxui 库
add_requires("gtest") -- google test
add_requires("boost", {configs = {all = true}}) -- boost 库
add_requires("eigen") -- 线性代数库
add_requires("range-v3")  -- 范围库
add_requires("stb") -- stb 
add_requires("magic_enum")  -- 枚举反射
add_requires("glm") -- glm opengl 线性代数库
add_requires("rapidjson") -- 一个 json 库
add_requires("spdlog") -- 一个日志库, 基于 fmt
add_requires("abseil") -- 补充标准库没有的常用功能
add_requires("benchmark") -- 谷歌性能评估框架
add_requires("glfw") -- glfw OpenGL 窗口和上下文管理
add_requires("libigl") -- 各种图形学算法大合集
add_requires("rttr") -- 反射库
add_requires("matplotplusplus") -- 
add_requires("gsl") -- 
add_requires("cgal") -- 
add_requires("ffmpeg") -- 音视频基础操作的库
add_requires("ncurses") -- 
add_requires("icu4c") -- C/C++ libraries for Unicode and globalization.

includes("学习过程中写的代码")
includes("代码片段")
