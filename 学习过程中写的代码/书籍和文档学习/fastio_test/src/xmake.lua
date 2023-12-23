for _, filepath in ipairs(os.files("./**.cpp")) do
target("fastio_test_" .. string.sub(filepath, 1, string.find(filepath, "\\") - 1) .. "_" .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost", "gtest", "fast_io")
end
