local PROJECT_NAME = path.basename(os.projectdir())

add_rules("mode.debug", "mode.release")

set_project(PROJECT_NAME)

add_requires("pcre2")

target("lib")
    set_basename(PROJECT_NAME)
    set_default(false)
    set_kind("static")
    set_languages("c11")
    set_version("2.0.0")
    
    add_files("src/*.c", "src/**/*.c", {excludes = "src/main.c"})
    add_packages("pcre2")

target("cli")
    set_basename(PROJECT_NAME)
    set_kind("binary")
    set_languages("c11")
    set_version("2.0.0")

    add_files("src/main.c")
    add_deps("lib")

    on_package(function (target)
        if is_mode("release") then
            import("scripts.package").package_release(target)
        end
    end)
