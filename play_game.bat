@echo off
cls
echo ========================================
echo     SO_LONG - Game Test
echo ========================================
echo.

REM Verificar se o executável existe
if not exist "so_long.exe" (
    echo [ERROR] so_long.exe not found!
    echo         Run build_simple.bat first
    echo.
    pause
    exit /b 1
)

REM Verificar se a pasta maps existe
if not exist "maps" (
    echo [WARNING] maps\ folder not found. Creating...
    mkdir maps
)

REM Verificar se level1.ber existe
if not exist "maps\level1.ber" (
    echo [WARNING] Creating default level1.ber...
    (
        echo 1111111111
        echo 1P00C00001
        echo 1000111001
        echo 1C00X00C01
        echo 1000111001
        echo 10000000E1
        echo 1111111111
    ) > maps\level1.ber
    echo [OK] level1.ber created
)

echo Starting game with error logging...
echo.
echo ========================================
echo   GAME OUTPUT:
echo ========================================
echo.

REM Executar e manter console aberto para ver erros
so_long.exe maps\level1.ber

echo.
echo ========================================
echo   GAME CLOSED
echo ========================================
echo.

if %ERRORLEVEL% NEQ 0 (
    echo [ERROR] Game exited with error code: %ERRORLEVEL%
    echo.
    echo Common issues:
    echo 1. Map file not found or invalid
    echo 2. Missing DLL files
    echo 3. Graphics driver issue
    echo.
    echo Try running: diagnose.bat
) else (
    echo [OK] Game closed normally
)

echo.
pause