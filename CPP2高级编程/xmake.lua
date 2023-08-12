for _, filepath in ipairs(os.files("./**.cpp")) do
target(path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost", "openssl", "jsoncpp", "ftxui", "gtest", "eigen", "ncurses")
end
