add_rules("mode.debug", "mode.release")

set_project("DanmakuFactory")

add_requires("pcre2")

target("cli")
    set_basename("DanmakuFactory")
    set_kind("binary")
    set_languages("c11", {strict = true})
    set_version("2.0.0")

    add_files("src/*.c")
    add_files("src/**/*.c")
    add_packages("pcre2")
