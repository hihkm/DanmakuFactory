add_rules("mode.debug", "mode.release")

add_requires("pcre2")

target("danmakufactory_core")
    add_cxflags("/utf-8")
    add_cxxflags("/utf-8")
    set_kind("shared")

    -- 添加soname
    if is_plat("linux") then
        add_shflags("-Wl,-soname,libdanmakufactory_core.so")
    end

    -- 添加正则表达式
    add_packages("pcre2")

    add_includedirs(
    "include",
    "../third_party/DanmakuFactory/src",
    "../third_party/DanmakuFactory/src/Define",
    "../third_party/DanmakuFactory/src/FileUtil"
    )

    add_files(
    "src/*.cpp",
    "src/*.c",
    "../third_party/DanmakuFactory/src/*.c|main.c",
    "../third_party/DanmakuFactory/src/**/*.c"
    )

    if is_plat("windows") then
        add_syslinks("shell32", "user32")
    end

    -- 强制将目标文件输出到 build/架构名 下，从而去掉 release 目录
    set_targetdir("build/$(plat)/$(arch)")