#拷贝danmaku_factory 的源文件

if(CMAKE_SYSTEM_NAME MATCHES "OHOS" OR OHOS)
    get_filename_component(DANMAKU_FACTORY_CORE_SRC_DIR "${CMAKE_SOURCE_DIR}/../../../../src" ABSOLUTE)
    get_filename_component(DANMAKU_FACTORY_CORE_DST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/DanmakuFactory/src" ABSOLUTE)

elseif(ANDROID)
    get_filename_component(DANMAKU_FACTORY_CORE_SRC_DIR "${CMAKE_SOURCE_DIR}/../../../../src" ABSOLUTE)
    get_filename_component(DANMAKU_FACTORY_CORE_DST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/DanmakuFactory/src" ABSOLUTE)

elseif(WIN32)
    get_filename_component(DANMAKU_FACTORY_CORE_SRC_DIR "${CMAKE_SOURCE_DIR}/../../../src" ABSOLUTE)
    get_filename_component(DANMAKU_FACTORY_CORE_DST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/DanmakuFactory/src" ABSOLUTE)

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(WARNING "copy danmaku factory core src: Linux")
    get_filename_component(DANMAKU_FACTORY_CORE_SRC_DIR "${CMAKE_SOURCE_DIR}/../../../src" ABSOLUTE)
    get_filename_component(DANMAKU_FACTORY_CORE_DST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/DanmakuFactory/src" ABSOLUTE)
elseif(APPLE)
    if(CMAKE_SYSTEM_NAME MATCHES "iOS")
        message(WARNING "copy danmaku factory core src: iOS")
    else()
        message(WARNING "copy danmaku factory core src: macOS")
    endif()
else()
    message(WARNING "copy danmaku factory core src err: ${CMAKE_SYSTEM_NAME}")
endif()

message(WARNING "copy src :${DANMAKU_FACTORY_CORE_SRC_DIR} ,target:${DANMAKU_FACTORY_CORE_DST_DIR}")

add_custom_target(COPY_DANMAKU_FACTORY_CORE ALL
        # 创建目录
        COMMAND ${CMAKE_COMMAND} -E make_directory "${DANMAKU_FACTORY_CORE_DST_DIR}"
        # 拷贝目录
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${DANMAKU_FACTORY_CORE_SRC_DIR}" "${DANMAKU_FACTORY_CORE_DST_DIR}"
)


