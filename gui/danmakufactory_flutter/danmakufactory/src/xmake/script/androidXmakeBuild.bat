@echo off
pushd %CD%

cd ..

:: 检查 arch
if "%~1"=="" (
    echo Error: No architecture provided
    echo Usage: %0 ^<arch^> [ndkPath]
    exit /b 1
)

set "arch=%~1"
set "ndkPath=%~2"

echo ===============================
echo Building Android for %arch%
if defined ndkPath (
    echo NDK path: %ndkPath%
) else (
    echo NDK path: not specified
)
echo ===============================

:: 如果提供了 NDK 路径且路径存在,则使用 --ndk 参数
if defined ndkPath (
    if exist "%ndkPath%" (
        xmake f -y -p android --ndk="%ndkPath%" -a %arch% -P .
    ) else (
        echo Warning: NDK path "%ndkPath%" does not exist, configuring without --ndk parameter
        xmake f -y -p android -a %arch% -P .
    )
) else (
    xmake f -y -p android -a %arch% -P .
)
if errorlevel 1 exit /b 1

xmake -P .
if errorlevel 1 exit /b 1

echo ===============================
echo Android build finished for %arch%
echo ===============================

popd