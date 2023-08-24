for _, filepath in ipairs(os.files("./**.cpp")) do
target('CPP并发编程实战_' .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost")
end
