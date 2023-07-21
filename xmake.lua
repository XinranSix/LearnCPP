add_rules("mode.debug", "mode.release")
set_languages("cxx20")

add_includedirs("include")

add_requires("fmt")
add_requires("ftxui")
add_requires("gtest")
add_requires("openssl")
add_requires("jsoncpp")
add_requires("boost", {configs = {all = true}})
add_requires("tbox", "zlib", "libpng","libsdl","libsdl_image")

includes("test")
includes("c_test")
includes("concurrency")
includes("modern_cpp")
includes("LicensePlateRecognition")

