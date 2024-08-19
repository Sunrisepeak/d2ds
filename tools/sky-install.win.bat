@Echo off
Setlocal
::EchoANSI.cmd
cls
:: Display a sample of all the ANSI colours.
:: Requires windows 1909 or newer

:: Define foreground and background ANSI colors:
Set _FBLACK=[30m
Set _BBLACK=[40m
Set _FRED=[31m
Set _BRED=[41m
Set _FGREEN=[32m
Set _BGREEN=[42m
Set _FYELLOW=[33m
Set _BYELLOW=[43m
Set _FBLUE=[34m
Set _BBLUE=[44m
Set _FMAG=[35m
Set _BMAG=[45m
Set _FCYAN=[36m
Set _BCYAN=[46m
Set _FLGRAY=[37m
Set _BLGRAY=[47m
Set _FDGRAY=[90m
Set _BDGRAY=[100m
Set _FBRED=[91m
Set _BBRED=[101m
Set _FBGREEN=[92m
Set _BBGREEN=[102m
Set _FBYELLOW=[93m
Set _BBYELLOW=[103m
Set _FBBLUE=[94m
Set _BBBLUE=[104m
Set _FBMAG=[95m
Set _BBMAG=[105m
Set _FBCYAN=[96m
Set _BBCYAN=[106m
Set _FBWHITE=[97m
Set _BBWHITE=[107m
Set _RESET=[0m

echo %_FBMAG%[d2ds]: start detect environment and try to auto config...

REM Check if xmake is installed
where xmake >nul 2>&1

IF %ERRORLEVEL% EQU 0 (
     echo %_FBGREEN%[d2ds]: xmake installed
) else (
    REM xmake is not installed, downloading and running install script using PowerShell
    echo %_FBMAG%[d2ds]: start install xmake...
    powershell -Command "Invoke-Expression ((Invoke-WebRequest 'https://xmake.io/psget.text' -UseBasicParsing).Content)"
)

REM Check if the extension is already installed
code --list-extensions | findstr /I /C:"ms-vscode.cpptools" >nul
if %ERRORLEVEL% equ 0 (
    echo %_FBGREEN%[d2ds]: vscode c++ extension installed
) else (
    echo %_FBMAG%[d2ds]: start install vscode c++ extension...
    call code --install-extension ms-vscode.cpptools
)

REM Colored echo
echo %_FBMAG%[d2ds]: auto config done.
echo.
echo  %_FYELLOW%  Dive into Data Structures pre-v0.0.1 - open-sources
echo.
Echo %_FCYAN%
echo - main-repo: https://github.com/Sunrisepeak/d2ds
echo - ebook: https://sunrisepeak.github.io/d2ds
echo - courses: https://sunrisepeak.github.io/d2ds-courses
echo - dstruct: https://github.com/Sunrisepeak/dstruct
echo - issues: https://github.com/Sunrisepeak/d2ds/issues
Echo %_RESET%
echo [d2ds]: Try running %_FRED%xmake dslings%_RESET% to start your d2ds coding...
echo [d2ds]: run %_FRED%xmake d2ds%_RESET% get more info



