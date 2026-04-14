@echo off

chcp 65001 >nul

pushd %CD%

cd ..

:: 检查是否提供了 ABI
if "%1"=="" (
    echo Error: No ABI provided!
    echo Usage: %0 ^<ABI^>
    echo Example: %0 x64

    exit /b 1
) else (
    set arch=%1
)

echo ===============================
echo Building Windows for %arch%
echo ===============================

:: 配置 xmake
xmake f -y -p windows -a %arch% -P .
if errorlevel 1 (
    echo Error: xmake f failed

    exit /b 1
)

:: 构建
xmake -P .
if errorlevel 1 (
    echo Error: xmake build failed

    exit /b 1
)

echo ===============================
echo Windows build finished for %arch%
echo ===============================

popd
