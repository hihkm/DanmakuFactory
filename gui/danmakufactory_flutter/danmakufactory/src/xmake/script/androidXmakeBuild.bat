@echo off
pushd %CD%

cd ..

:: 检查 arch
if "%~1"=="" (
    echo Error: No architecture provided
    echo Usage: %0 ^<arch^> ^<ndkPath^>
    exit /b 1
)

:: 检查 ndk
if "%~2"=="" (
    echo Error: No NDK path provided
    echo Usage: %0 ^<arch^> ^<ndkPath^>
    exit /b 1
)

set "arch=%~1"
set "ndkPath=%~2"

echo ===============================
echo Building Android for %arch%
echo NDK path: %ndkPath%
echo ===============================

xmake f -y -p android --ndk="%ndkPath%" -a %arch% -P .
if errorlevel 1 exit /b 1

xmake -P .
if errorlevel 1 exit /b 1

echo ===============================
echo Android build finished for %arch%
echo ===============================

popd