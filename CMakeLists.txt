cmake_minimum_required(VERSION 3.15...4.0)

project(DanmakuFactory LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
        add_compile_options(/wd4819)
        add_compile_options(/wd4996)
endif()

add_subdirectory(pcre2)

add_executable (DanmakuFactory JsonFile.c main.c XmlFile.c
                AssFile/AssFile.c AssFile/AssStringProcessing.c Config/Config.c
                List/DanmakuFactoryList.c String/DanmakuFactoryString.c TemplateFile/TemplateFile.c)

target_link_libraries(DanmakuFactory PRIVATE pcre2-8)

install(TARGETS DanmakuFactory
        CONFIGURATIONS Release
        RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin)
