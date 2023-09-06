for _, filepath in ipairs(os.files("./**.cpp")) do
target("现代CPP语言核心特性解析_" .. string.sub(filepath, 1, string.find(filepath, "/") - 1) .. "_" .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost", "range-v3", "gtest", "magic_enum", "cpprest")
end
