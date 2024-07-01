@echo off

REM set ansi color - TODO: support log-color
set "RED=%ESC%[31m"
set "GREEN=%ESC%[32m"
set "YELLOW=%ESC%[33m"
set "PURPLE=%ESC%[35m"
set "CYAN=%ESC%[36m"
set "RESET=%ESC%[0m"

echo [d2ds]: start detect environment and try to auto config...

REM Check if xmake is installed
where xmake >nul 2>&1

IF %ERRORLEVEL% EQU 0 (
    echo [d2ds]: xmake installed
) else (
    REM xmake is not installed, downloading and running install script using PowerShell
    echo [d2ds]: start install xmake...
    powershell -Command "Invoke-Expression ((Invoke-WebRequest 'https://xmake.io/psget.text' -UseBasicParsing).Content)"
)

REM Check if the extension is already installed
code --list-extensions | findstr /I /C:"ms-vscode.cpptools" >nul
if %ERRORLEVEL% equ 0 (
    echo [d2ds]: vscode c++ extension installed
) else (
    echo [d2ds]: start install vscode c++ extension...
    call code --install-extension ms-vscode.cpptools
)

REM Colored echo
echo [d2ds]: auto config done.
echo \tDive into Data Structures pre-v0.0.1 - open-sources
echo.
echo - main-repo: https://github.com/Sunrisepeak/d2ds
echo - ebook: https://sunrisepeak.github.io/d2ds
echo - courses: https://sunrisepeak.github.io/d2ds-courses
echo - dstruct: https://github.com/Sunrisepeak/dstruct
echo - issues: https://github.com/Sunrisepeak/d2ds/issues
echo.
echo [d2ds]: Try running xmake dslings to start your d2ds coding...
echo [d2ds]: run xmake d2ds get more info

:END