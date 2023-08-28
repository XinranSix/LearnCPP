add_includedirs("./include")

for _, filepath in ipairs(os.files("./**.cpp")) do
target('CPP20高级编程_' .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost", "range-v3", "gtest")
end
