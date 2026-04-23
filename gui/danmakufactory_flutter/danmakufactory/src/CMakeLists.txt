cmake_minimum_required(VERSION 3.10)

project(danmakufactory_library VERSION 0.0.1 LANGUAGES C)


#鸿蒙的配置
#set(OHOS_NATIVE_SDK "C:/Users/moli/soft/devecostudio/sdk/default/openharmony/native")
set(OHOS_NATIVE_SDK "D:/sofe/devecostudio/sdk/default/openharmony/native")


#定义名称
set(DANMAKU_FACTORY_CORE_LIB_NAME "danmakufactory_core")

message(WARNING "=== Device Info ===")
message(WARNING "CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}")
message(WARNING "CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(WARNING "ANDROID : ${ANDROID}")
message(WARNING "CMAKE_ANDROID_NDK : ${CMAKE_ANDROID_NDK}")
message(WARNING "ANDROID_NDK : ${ANDROID_NDK}")
message(WARNING "OHOS : ${OHOS}")
message(WARNING "WIN32 : ${WIN32}")
message(WARNING "APPLE : ${APPLE}")
message(WARNING "CMAKE_SOURCE_DIR :${CMAKE_SOURCE_DIR}")
message(WARNING "CMAKE_CURRENT_SOURCE_DIR :${CMAKE_CURRENT_SOURCE_DIR}")
message(WARNING "CMAKE_CURRENT_LIST_DIR :${CMAKE_CURRENT_LIST_DIR}")
message(WARNING "====================")


#xmake的一些目录
if (WIN32)
    string(REPLACE "windows/flutter/ephemeral/.plugin_symlinks/" "" XMAKE_FILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xmake")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    string(REPLACE "linux/flutter/ephemeral/.plugin_symlinks/" "" XMAKE_FILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xmake")
elseif(APPLE)
    if(CMAKE_SYSTEM_NAME MATCHES "iOS")
    else()
        string(REPLACE "macos/Flutter/ephemeral/.symlinks/plugins/" "" XMAKE_FILE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/xmake")
    endif()
else()
    set(XMAKE_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/xmake)
endif()

message(WARNING "XMAKE_FILE_DIR : ${XMAKE_FILE_DIR}")

set(XMAKE_BUILD_SCRIPT ${XMAKE_FILE_DIR}/script)
set(XMAKE_BUILD_OUTPUT ${XMAKE_FILE_DIR}/build)

if (MSVC)
    add_compile_options(/utf-8)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/log
)

#添加源文件拷贝任务
include(${CMAKE_CURRENT_LIST_DIR}/cmake/copy_danmaku_factory_core.cmake)


# 添加xmake编译的danmakufactory_core
add_library(${DANMAKU_FACTORY_CORE_LIB_NAME} SHARED IMPORTED)

if(CMAKE_SYSTEM_NAME MATCHES "OHOS" OR OHOS)
    message(WARNING "Compiling: OHOS")

    # 定义xmake鸿蒙编译的so输出路径
    set(XMAKE_OH_BUILD_OUTPUT_SO ${XMAKE_BUILD_OUTPUT}/harmony/${OHOS_ARCH}/lib${DANMAKU_FACTORY_CORE_LIB_NAME}.so)
    # 定义鸿蒙标准的 so 存放路径,这个路径下的so才会被打包进app
    set(OHOS_DEFAULT_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ohos/libs/${OHOS_ARCH})

    # 设置xmake编译的danmakufactory_core的导入规则
    set_target_properties(${DANMAKU_FACTORY_CORE_LIB_NAME} PROPERTIES
        IMPORTED_NO_SONAME TRUE
        IMPORTED_LOCATION ${XMAKE_OH_BUILD_OUTPUT_SO}
    )

    # 执行编译脚本xmake生成文件,并在生成后自动拷贝
    add_custom_command(
        OUTPUT "${XMAKE_OH_BUILD_OUTPUT_SO}"
        # 设置工作目录
        WORKING_DIRECTORY "${XMAKE_FILE_DIR}"
        # 执行 oh xmake 编译脚本
        COMMAND xmake f -y -p harmony -a ${OHOS_ARCH} --sdk=${OHOS_NATIVE_SDK} --bin=${OHOS_NATIVE_SDK}/llvm/bin -P .
        COMMAND xmake -P .
        # 创建目录
        COMMAND ${CMAKE_COMMAND} -E make_directory "${OHOS_DEFAULT_LIBS_DIR}"
        # 拷贝生成文件到打包目录
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${XMAKE_OH_BUILD_OUTPUT_SO}" "${OHOS_DEFAULT_LIBS_DIR}"
        COMMENT "=> 正在执行 xmake 编译并拷贝"
        VERBATIM
    )

    # 包装成一个构建目标
    add_custom_target(BUILD_XMAKE_DANMAKU_CORE DEPENDS "${XMAKE_OH_BUILD_OUTPUT_SO}")
    # 依赖copy源文件
    add_dependencies(BUILD_XMAKE_DANMAKU_CORE COPY_DANMAKU_FACTORY_CORE)

elseif(ANDROID)
    message(WARNING "Compiling: Android")
    # 定义xmake Android编译的so输出路径
    set(XMAKE_ANDROID_BUILD_OUTPUT_SO ${XMAKE_BUILD_OUTPUT}/android/${ANDROID_ABI}/lib${DANMAKU_FACTORY_CORE_LIB_NAME}.so)
    # 定义Android标准的 so 存放路径,这个路径下的so才会被打包进app
    set(ANDROID_DEFAULT_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../android/src/main/jniLibs/${ANDROID_ABI})

    # 设置xmake编译的danmakufactory_core的导入规则
    set_target_properties(${DANMAKU_FACTORY_CORE_LIB_NAME} PROPERTIES
        IMPORTED_NO_SONAME TRUE
        IMPORTED_LOCATION ${XMAKE_ANDROID_BUILD_OUTPUT_SO}
    )

    # 执行编译脚本xmake生成文件,并在生成后自动拷贝
    add_custom_command(
        OUTPUT "${XMAKE_ANDROID_BUILD_OUTPUT_SO}"
        # 设置工作目录
        WORKING_DIRECTORY "${XMAKE_FILE_DIR}"
        # 执行 Android xmake 编译脚本
        COMMAND xmake f -y -p android --ndk=${CMAKE_ANDROID_NDK} -a ${ANDROID_ABI} -P .
        COMMAND xmake -P .
        # 创建目录
        COMMAND ${CMAKE_COMMAND} -E make_directory "${ANDROID_DEFAULT_LIBS_DIR}"
        # 拷贝生成文件到安卓 jniLibs 打包目录
        COMMAND ${CMAKE_COMMAND} -E copy "${XMAKE_ANDROID_BUILD_OUTPUT_SO}" "${ANDROID_DEFAULT_LIBS_DIR}"
        COMMENT "=> 正在执行 xmake 编译并拷贝"
        VERBATIM
    )

    # 包装成一个构建目标
    add_custom_target(BUILD_XMAKE_DANMAKU_CORE DEPENDS "${XMAKE_ANDROID_BUILD_OUTPUT_SO}")
    # 依赖copy源文件
    add_dependencies(BUILD_XMAKE_DANMAKU_CORE COPY_DANMAKU_FACTORY_CORE)

elseif(WIN32)
    message(WARNING "Compiling: Windows")

    # 判断架构
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(WIN_ABI_NAME x64)
    else()
        set(WIN_ABI_NAME x86)
    endif()

    # 定义xmake Win编译输出路径
    set(XMAKE_WIN_BUILD_OUTPUT ${XMAKE_BUILD_OUTPUT}/windows/${WIN_ABI_NAME})
    # 定义xmake Win编译的dll输出路径
    set(XMAKE_WIN_BUILD_OUTPUT_DLL ${XMAKE_WIN_BUILD_OUTPUT}/${DANMAKU_FACTORY_CORE_LIB_NAME}.dll)
    # 设置xmake编译的danmakufactory_core的导入规则,包括lib
    set_target_properties(${DANMAKU_FACTORY_CORE_LIB_NAME} PROPERTIES
        IMPORTED_NO_SONAME TRUE
        IMPORTED_LOCATION ${XMAKE_WIN_BUILD_OUTPUT_DLL}
        IMPORTED_IMPLIB ${XMAKE_WIN_BUILD_OUTPUT}/${DANMAKU_FACTORY_CORE_LIB_NAME}.lib
    )

    # 执行xmake命令生成文件,并在生成后自动拷贝
    # win执行脚本的时候可能有些文件会被占用,如果一致失败可以尝试手动执行xmake
    add_custom_command(
        OUTPUT "${XMAKE_WIN_BUILD_OUTPUT_DLL}"
        # 设置工作目录
        WORKING_DIRECTORY "${XMAKE_FILE_DIR}"
        # 执行批处理文件
        #COMMAND cmd.exe /c "${XMAKE_BUILD_SCRIPT}/winXmakeBuild.bat" "${WIN_ABI_NAME}"
        COMMAND cmd.exe /c "xmake f -y -p windows -a ${WIN_ABI_NAME} -P ."
        COMMAND cmd.exe /c "xmake -P ."
        # 创建目录
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/runner/Debug"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/runner/Release"
        # 拷贝生成文件到打包目录
        COMMAND ${CMAKE_COMMAND} -E copy "${XMAKE_WIN_BUILD_OUTPUT_DLL}" "${CMAKE_BINARY_DIR}/runner/Debug"
        COMMAND ${CMAKE_COMMAND} -E copy "${XMAKE_WIN_BUILD_OUTPUT_DLL}" "${CMAKE_BINARY_DIR}/runner/Release"
        COMMENT "=> 正在执行 xmake 编译并拷贝"
        VERBATIM
    )

    # 包装成一个构建目标
    add_custom_target(BUILD_XMAKE_DANMAKU_CORE DEPENDS "${XMAKE_WIN_BUILD_OUTPUT_DLL}")
    # 依赖copy源文件
    add_dependencies(BUILD_XMAKE_DANMAKU_CORE COPY_DANMAKU_FACTORY_CORE)


elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(WARNING "Compiling: Linux")
    # 获取当前架构(去除换行)
    execute_process(
        COMMAND uname -m
        OUTPUT_VARIABLE LINUX_ARCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    # 定义xmake Linux编译的so输出路径
    set(XMAKE_LINUX_BUILD_OUTPUT_SO ${XMAKE_BUILD_OUTPUT}/linux/${LINUX_ARCH}/lib${DANMAKU_FACTORY_CORE_LIB_NAME}.so)
    # 定义Linux标准的 so 存放路径
    set(LINUX_DEFAULT_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../linux/libs/${LINUX_ARCH})

    # 设置xmake编译的danmakufactory_core的导入规则
    set_target_properties(${DANMAKU_FACTORY_CORE_LIB_NAME} PROPERTIES
        IMPORTED_NO_SONAME TRUE
        IMPORTED_LOCATION ${XMAKE_LINUX_BUILD_OUTPUT_SO}
    )

    # 执行编译脚本xmake生成文件,并在生成后自动拷贝
    add_custom_command(
        OUTPUT "${XMAKE_LINUX_BUILD_OUTPUT_SO}"
        # 设置工作目录
        WORKING_DIRECTORY "${XMAKE_FILE_DIR}"
        # 执行 Linux xmake 编译脚本
        COMMAND xmake f -y -p linux -a ${LINUX_ARCH} -P .
        COMMAND xmake -P .
        # 创建目录
        COMMAND ${CMAKE_COMMAND} -E make_directory "${LINUX_DEFAULT_LIBS_DIR}"
        # 拷贝生成文件到打包目录
        COMMAND ${CMAKE_COMMAND} -E copy "${XMAKE_LINUX_BUILD_OUTPUT_SO}" "${LINUX_DEFAULT_LIBS_DIR}"
        COMMENT "=> 正在执行 xmake 编译并拷贝"
        VERBATIM
    )

    # 包装成一个构建目标
    add_custom_target(BUILD_XMAKE_DANMAKU_CORE DEPENDS "${XMAKE_LINUX_BUILD_OUTPUT_SO}")
    # 依赖copy源文件
    add_dependencies(BUILD_XMAKE_DANMAKU_CORE COPY_DANMAKU_FACTORY_CORE)

    install(FILES "${XMAKE_LINUX_BUILD_OUTPUT_SO}" DESTINATION "lib")

elseif(APPLE)
    if(CMAKE_SYSTEM_NAME MATCHES "iOS")
        message(WARNING "Compiling: iOS")
    else()
        message(WARNING "Compiling: macOS")
        # 获取 macOS 架构
        set(MACOS_ARCH "${CMAKE_OSX_ARCHITECTURES}")
        if(NOT MACOS_ARCH)
            execute_process(
                COMMAND uname -m
                OUTPUT_VARIABLE MACOS_ARCH
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
        endif()
        message(WARNING "MACOS_ARCH:${MACOS_ARCH}")

        set(XMAKE_MACOS_BUILD_OUTPUT_ROOT_DIR ${XMAKE_BUILD_OUTPUT}/macosx)
        # 定义xmake macOS编译的dylib输出路径
        set(XMAKE_MACOS_BUILD_OUTPUT_DYLIB ${XMAKE_MACOS_BUILD_OUTPUT_ROOT_DIR}/${MACOS_ARCH}/lib${DANMAKU_FACTORY_CORE_LIB_NAME}.dylib)
        # x86_64
        set(XMAKE_MACOS_X86_64_BUILD_OUTPUT_DYLIB ${XMAKE_MACOS_BUILD_OUTPUT_ROOT_DIR}/x86_64/lib${DANMAKU_FACTORY_CORE_LIB_NAME}.dylib)
        # universal
        set(XMAKE_MACOS_UNIVERSAL_BUILD_OUTPUT_DYLIB ${XMAKE_MACOS_BUILD_OUTPUT_ROOT_DIR}/lib${DANMAKU_FACTORY_CORE_LIB_NAME}.dylib)
        # 定义macOS标准的库存放路径
        set(MACOS_DEFAULT_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../macos/libs)

        # 设置xmake编译的danmakufactory_core的导入规则
        set_target_properties(${DANMAKU_FACTORY_CORE_LIB_NAME} PROPERTIES
            IMPORTED_NO_SONAME TRUE
            IMPORTED_LOCATION ${XMAKE_MACOS_BUILD_OUTPUT_DYLIB}
        )

        # 执行编译脚本xmake生成文件,并在生成后自动拷贝
        add_custom_command(
            OUTPUT "${XMAKE_MACOS_BUILD_OUTPUT_DYLIB}"
            # 设置工作目录
            WORKING_DIRECTORY "${XMAKE_FILE_DIR}"
            # 执行 macOS xmake 编译脚本
            COMMAND xmake f -y -p macosx -a ${MACOS_ARCH} -P .
            COMMAND xmake -P .
            # 还需要x86_64才能打包,开发环境不需要,这里可以优化
            COMMAND xmake f -y -p macosx -a x86_64 -P .
            COMMAND xmake -P .
            # 创建目录
            COMMAND ${CMAKE_COMMAND} -E make_directory "${MACOS_DEFAULT_LIBS_DIR}"
            # lipo
            COMMAND lipo -create -output ${XMAKE_MACOS_UNIVERSAL_BUILD_OUTPUT_DYLIB} ${XMAKE_MACOS_BUILD_OUTPUT_DYLIB} ${XMAKE_MACOS_X86_64_BUILD_OUTPUT_DYLIB}
            # 拷贝生成文件到打包目录
            COMMAND ${CMAKE_COMMAND} -E copy "${XMAKE_MACOS_UNIVERSAL_BUILD_OUTPUT_DYLIB}" "${MACOS_DEFAULT_LIBS_DIR}"
            COMMENT "=> 正在执行 xmake macOS 编译并拷贝"
            VERBATIM
        )

        # 包装成一个构建目标
        add_custom_target(BUILD_XMAKE_DANMAKU_CORE DEPENDS "${XMAKE_MACOS_BUILD_OUTPUT_DYLIB}")
        # 依赖copy源文件
        add_dependencies(BUILD_XMAKE_DANMAKU_CORE COPY_DANMAKU_FACTORY_CORE)

        install(FILES "${XMAKE_MACOS_BUILD_OUTPUT_DYLIB}" DESTINATION "lib")

    endif()
else()
    message(WARNING "Compiling err: ${CMAKE_SYSTEM_NAME}")
endif()


add_library(danmakufactory SHARED
  "danmakufactory.c"
)

set_target_properties(danmakufactory PROPERTIES
  PUBLIC_HEADER danmakufactory.h
  OUTPUT_NAME "danmakufactory"
  BUILD_WITH_INSTALL_RPATH TRUE
  INSTALL_RPATH "$ORIGIN"
)

target_compile_definitions(danmakufactory PUBLIC DART_SHARED_LIB)

# 主工程依赖执行编译脚本xmake生成文件
add_dependencies(danmakufactory BUILD_XMAKE_DANMAKU_CORE)

#链接core
target_link_libraries(danmakufactory ${DANMAKU_FACTORY_CORE_LIB_NAME})

if (ANDROID)
  find_library(log-lib log)
  target_link_libraries(danmakufactory
      ${log-lib}
  )
  # Support Android 15 16k page size
  target_link_options(danmakufactory PRIVATE "-Wl,-z,max-page-size=16384")
elseif(CMAKE_SYSTEM_NAME MATCHES "OHOS" OR OHOS)
  target_link_libraries(danmakufactory
      libhilog_ndk.z.so
  )
endif()
