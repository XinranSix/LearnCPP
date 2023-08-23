for _, filepath in ipairs(os.files("./**.cpp")) do
target('函数式编程' .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("gtest", "fmt")
end
