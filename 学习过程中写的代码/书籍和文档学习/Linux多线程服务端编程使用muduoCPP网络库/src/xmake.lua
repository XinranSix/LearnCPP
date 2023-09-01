for _, filepath in ipairs(os.files("./**.cpp")) do
target('Linux多线程服务端编程使用muduoCPP网络库_' .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost", "range-v3", "gtest", "magic_enum", "cpprest")
end
