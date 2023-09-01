for _, filepath in ipairs(os.files("./**.cpp")) do
target('Linux高性能服务器编程_' .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
end
