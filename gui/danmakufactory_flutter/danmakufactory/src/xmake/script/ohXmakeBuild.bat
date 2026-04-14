@echo off

pushd %CD%

cd ..

:: 检查是否提供了 ABI
if "%1"=="" (
    echo Error: No ABI provided!
    echo Usage: %0 ^<ABI^> ^<SDK_PATH^>
    echo Example: %0 arm64-v8a D:/sofe/devecostudio/sdk/default/openharmony/native
    
    exit /b 1
) else (
    set arch=%1
)

:: 检查是否提供了 SDK 路径
if "%2"=="" (
    echo Error: No SDK path provided!
    echo Usage: %0 ^<ABI^> ^<SDK_PATH^>
    echo Example: %0 arm64-v8a D:/sofe/devecostudio/sdk/default/openharmony/native
    
    exit /b 1
) else (
    set SDK=%2
)

:: 设置 LLVM bin
set BIN=%SDK%/llvm/bin

echo ===============================
echo Building Harmony for %arch%
echo SDK path: %SDK%
echo ===============================

:: 配置 xmake
xmake f -y -p harmony -a %arch% --sdk=%SDK% --bin=%BIN% -P .
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
echo Harmony build finished for %arch%
echo ===============================

popd
