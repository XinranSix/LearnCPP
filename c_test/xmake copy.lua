for _, filepath in ipairs(os.files("./**.c")) do
    target(path.basename(filepath))
        add_files(filepath)
    end
    