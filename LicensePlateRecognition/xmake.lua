for _, filepath in ipairs(os.files("./**.cpp")) do
target(path.basename(filepath))
    set_kind("binary")
    add_files(filepath)
    add_packages("openssl", "jsoncpp")
    add_links("jsoncpp", "curl")
    after_build(function (target)
        os.cp("images", target:targetdir())
    end)
end
