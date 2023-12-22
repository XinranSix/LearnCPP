for _, filepath in ipairs(os.files("./**.cpp")) do
target("Qt6CPP开发指南_" .. string.sub(filepath, 1, string.find(filepath, "\\") - 1) .. "_" .. path.basename(filepath))
    add_files(filepath)
    add_rules("qt.console")
end
