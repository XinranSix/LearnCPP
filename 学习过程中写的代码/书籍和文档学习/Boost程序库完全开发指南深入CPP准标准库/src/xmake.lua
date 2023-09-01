for _, filepath in ipairs(os.files("./**.cpp")) do
target("Boost程序库完全开发指南深入CPP准标准库_" .. string.sub(filepath, 1, string.find(filepath, "/") - 1) .. "_" .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost", "range-v3", "gtest", "magic_enum", "cpprest")
end
