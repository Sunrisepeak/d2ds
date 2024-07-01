@echo off

REM set ansi color
set "ESC="
for /F "delims=" %%i in ('echo prompt $E ^& for %%E in (1) do rem') do set "ESC=%%i"
set "RED=%ESC%[31m"
set "GREEN=%ESC%[32m"
set "YELLOW=%ESC%[33m"
set "PURPLE=%ESC%[35m"
set "CYAN=%ESC%[36m"
set "RESET=%ESC%[0m"

REM checker ansi color support
for /F "delims=" %%i in ('ver') do set version=%%i
if "%version:~22,2%" GEQ "10" (
    >nul 2>&1 reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1 /f
)

echo %GREEN%[d2ds]: start detect environment and try to auto config...%RESET%

REM Check if xmake is installed
where xmake >nul 2>&1

IF %ERRORLEVEL% EQU 0 (
    echo %PURPLE%[d2ds]: xmake installed%RESET%
) else (
    REM xmake is not installed, downloading and running install script using PowerShell
    echo %PURPLE%[d2ds]: start install xmake...%RESET%
    powershell -Command "Invoke-Expression ((Invoke-WebRequest 'https://xmake.io/psget.text' -UseBasicParsing).Content)"
)

REM Check if the extension is already installed
code --list-extensions | findstr /I /C:"ms-vscode.cpptools" >nul
if %ERRORLEVEL% equ 0 (
    echo %GREEN%[d2ds]: vscode c++ extension installed%RESET%
) else (
    echo %PURPLE%[d2ds]: start install vscode c++ extension...%RESET%
    code --install-extension ms-vscode.cpptools
)

REM Colored echo
echo %PURPLE%[d2ds]: auto config done.%RESET%
echo %YELLOW%    Dive into Data Structures pre-v0.0.1 - open-sources%RESET%
echo.
echo %CYAN% - main-repo: https://github.com/Sunrisepeak/d2ds%RESET%
echo %CYAN% - ebook: https://sunrisepeak.github.io/d2ds%RESET%
echo %CYAN% - courses: https://sunrisepeak.github.io/d2ds-courses%RESET%
echo %CYAN% - dstruct: https://github.com/Sunrisepeak/dstruct%RESET%
echo %CYAN% - issues: https://github.com/Sunrisepeak/d2ds/issues%RESET%
echo.
echo [d2ds]: Try running %RED%xmake dslings%RESET% to start your d2ds coding...
echo [d2ds]: run %RED%xmake d2ds%RESET% get more info

:END