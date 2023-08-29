add_includedirs("./include")

for _, filepath in ipairs(os.files("./**.cpp")) do
target('CPP20设计模式可复用的面向对象设计方法_' .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost", "range-v3", "gtest", "magic_enum")
end
