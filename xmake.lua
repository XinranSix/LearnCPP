add_rules("mode.debug", "mode.release")
set_languages("cxx20")

add_includedirs("include")

add_requires("ftxui")
add_requires("fmt", "gtest")
add_requires("boost", {configs = {all = true}})
add_requires("tbox", "zlib", "libpng","libsdl","libsdl_image")

includes("c_test")
includes("test")
includes("sort")
includes("concurrency")
includes("modern_cpp")

