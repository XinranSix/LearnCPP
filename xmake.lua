add_rules("mode.debug", "mode.release")
set_languages("cxx20")

add_includedirs("include")

add_requires("fmt") -- fmt 库
add_requires("ftxui") -- ftxui 库
add_requires("gtest") -- google test
add_requires("openssl") -- openssl
add_requires("jsoncpp") -- jsoncpp
add_requires("boost", {configs = {all = true}}) -- boost
add_requires("tbox", "zlib", "libpng","libsdl","libsdl_image")

if is_plat("windows") then
    add_cxflags("/utf-8", "/std:c++20")
else
    add_cxflags("-fexec-charset=UTF-8", "-fextended-identifiers", "-finput-charset=UTF-8")
end

includes("c_test")
includes("cpp_test")
includes("concurrency")
includes("LicensePlateRecognition")

