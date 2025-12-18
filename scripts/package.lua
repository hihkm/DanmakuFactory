function package_release(target)
    -- 创建临时工作目录
    local tmp_dir = path.join(os.tmpdir(), "danmaku_package")
    os.mkdir(tmp_dir)
    os.rm(path.join(tmp_dir, "*")) -- 清空临时目录

    -- 复制可执行文件
    os.cp(target:targetfile(), tmp_dir)

    -- 复制文档文件
    local docs_dir = path.join(os.projectdir(), "docs")
    if os.isdir(docs_dir) then
        os.cp(path.join(docs_dir, "*"), tmp_dir)
    end

    -- 列出临时目录内容，便于调试
    print(os.filedirs(tmp_dir .. "/**"))

    -- 创建打包目录
    local package_dir = path.join(os.projectdir(), 'build', "packages")
    os.mkdir(package_dir)

    -- 生成压缩包名称
    local package_name = ("%s-dev-%s-%s-CLI"):format(target:basename(), os.host(), os.arch())
    local package_path = path.join(package_dir, package_name)

    -- 执行打包（跨平台兼容）
    print("Packaging %s...", package_name)
    if is_plat("windows") then
        package_path = package_path .. ".zip"
        os.execv("powershell", {"-Command",
                                string.format(
            "Compress-Archive -Path '%s\\*' -DestinationPath '%s' -Force -CompressionLevel Optimal", tmp_dir,
            package_path)})
    else
        package_path = package_path .. ".tar.gz"
        os.execv("tar", {"--use-compress-program", "gzip -9", "-cvf", package_path, "-C", tmp_dir, "."})
    end

    -- 清理临时目录
    os.rm(tmp_dir)

    print("Package created: %s", package_path)
end

return package_release
