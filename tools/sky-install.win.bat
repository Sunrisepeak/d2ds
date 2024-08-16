@Echo off
Setlocal
::EchoANSI.cmd
cls
:: Display a sample of all the ANSI colours.
:: Requires windows 1909 or newer

:: Define foreground and background ANSI colors:
Set _fBlack=[30m
Set _bBlack=[40m
Set _fRed=[31m
Set _bRed=[41m
Set _fGreen=[32m
Set _bGreen=[42m
Set _fYellow=[33m
Set _bYellow=[43m
Set _fBlue=[34m
Set _bBlue=[44m
Set _fMag=[35m
Set _bMag=[45m
Set _fCyan=[36m
Set _bCyan=[46m
Set _fLGray=[37m
Set _bLGray=[47m
Set _fDGray=[90m
Set _bDGray=[100m
Set _fBRed=[91m
Set _bBRed=[101m
Set _fBGreen=[92m
Set _bBGreen=[102m
Set _fBYellow=[93m
Set _bBYellow=[103m
Set _fBBlue=[94m
Set _bBBlue=[104m
Set _fBMag=[95m
Set _bBMag=[105m
Set _fBCyan=[96m
Set _bBCyan=[106m
Set _fBWhite=[97m
Set _bBWhite=[107m
Set _RESET=[0m

echo %_fBMag%[d2ds]: start detect environment and try to auto config...

REM Check if xmake is installed
where xmake >nul 2>&1

IF %ERRORLEVEL% EQU 0 (
     echo %_fBGreen%[d2ds]: xmake installed
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
echo %_fBMag%[d2ds]: auto config done.
echo.
echo  %_fYellow%  Dive into Data Structures pre-v0.0.1 - open-sources
echo.
echo %_fCyan%- main-repo: https://github.com/Sunrisepeak/d2ds
echo - ebook: https://sunrisepeak.github.io/d2ds
echo - courses: https://sunrisepeak.github.io/d2ds-courses
echo - dstruct: https://github.com/Sunrisepeak/dstruct
echo - issues: https://github.com/Sunrisepeak/d2ds/issues
Echo %_RESET%
echo [d2ds]: Try running %_fYellow%xmake dslings%_RESET% to start your d2ds coding...
echo [d2ds]: run %_fYellow%xmake d2ds%_RESET% get more info

:: reset
Echo %_RESET%



:: SS64.com

pause