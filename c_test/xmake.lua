for _, filepath in ipairs(os.files("./**.c")) do
target(path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
end