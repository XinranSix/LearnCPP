for _, filepath in ipairs(os.files("./**.cpp")) do
target('TheBoostCPPLibraries_' .. path.basename(filepath))
    add_files(filepath)
    set_rundir(path.directory(filepath))
    add_packages("fmt", "boost")
end
