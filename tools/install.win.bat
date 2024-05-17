@echo off
REM Check if xmake is installed
where xmake >nul 2>&1

IF %ERRORLEVEL% EQU 0 (
    echo xmake installed
    GOTO END
)

REM xmake is not installed, downloading and running install script using PowerShell
powershell -Command "Invoke-Expression ((Invoke-WebRequest 'https://xmake.io/psget.text' -UseBasicParsing).Content)"

:END