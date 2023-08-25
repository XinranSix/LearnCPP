for _, filepath in ipairs(os.files("./**.cpp")) do
target('CPP函数式编程_' .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost", "range-v3")
end
