for _, filepath in ipairs(os.files("./**.cpp")) do
target('代码片段_' ..path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("gtest", "fmt")
end
