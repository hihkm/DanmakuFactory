local PROJECT_NAME = path.basename(os.projectdir())
local LIB_VERSION = "2.0.0"
local CLI_VERSION = "2.0.0"

set_project(PROJECT_NAME)
set_version("2.0.0")

add_requires("pcre2")
add_rules("mode.debug", "mode.release")

target("lib-static")
    set_basename(PROJECT_NAME)
    set_default(false)
    set_kind("static")
    set_languages("c11")
    set_version(LIB_VERSION)

    add_files("src/**/*.c")
    add_includedirs("include", {public = true})
    add_includedirs("src", {public = true})
    add_packages("pcre2")

target("cli")
    set_basename(PROJECT_NAME)
    set_kind("binary")
    set_languages("c11")
    set_version(CLI_VERSION)

    add_files("src/main.c")
    add_deps("lib-static")

    on_package(function (target)
        if is_mode("release") then
            import("scripts.package").package_release(target)
        end
    end)

task("format")
    on_run(function ()
        import("core.base.option")
        import("lib.detect.find_tool")
        
        local tool = find_tool("clang-format")
        if not tool then
            raise("clang-format not found!")
        end

        local files = option.get("files") or {"src/**", "include/**"}
        for _, pattern in ipairs(files) do
            local filelist = os.files(pattern)
            for _, file in ipairs(filelist) do
                os.execv(tool.program, {"-i", file})
                print("Formatting file:", file)
            end
        end
    end)
    
    set_menu {
        usage = "xmake format [options]",
        description = "Format code files",
        options = {
            {'f', "files", "vs", nil, "File patterns to format"}
        }
    }
