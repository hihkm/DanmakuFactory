add_rules("mode.debug", "mode.release")

set_project("DanmakuFactory")

add_requires("pcre2")

target("cli")
    set_basename("DanmakuFactory")
    set_kind("binary")
    set_languages("c11")
    set_version("2.0.0", {build = "%Y%m%d%H%M"})

    add_files("src/*.c", "src/**/*.c")

    add_packages("pcre2")
