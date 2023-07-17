add_requires("fmt", "gtest")
add_requires("tbox", "zlib", "libpng","libsdl","libsdl_image")
set_languages("cxx20")
add_rules("mode.debug", "mode.release")

add_includedirs("include")

includes("c_test")
includes("test")
includes("sort")

