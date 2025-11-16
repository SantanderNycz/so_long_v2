@echo off
cls
echo ========================================
echo     SO_LONG - Windows Build
echo ========================================
echo.

REM Verificar GCC
where gcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: GCC not found!
    echo Install MinGW-w64 or MSYS2
    pause
    exit /b 1
)

REM Limpar
if exist so_long.exe del so_long.exe
if exist obj rmdir /s /q obj
mkdir obj

echo Compiling...
echo.

gcc -Wall -O2 -std=c99 ^
    -I./includes ^
    -I./raylib/include ^
    sources/animation.c ^
    sources/check_solvability.c ^
    sources/check.c ^
    sources/enemy_funct.c ^
    sources/imgs.c ^
    sources/maps_funct.c ^
    sources/move.c ^
    sources/render.c ^
    sources/so_long.c ^
    sources/utils.c ^
    -L./raylib/lib ^
    -lraylib ^
    -lopengl32 ^
    -lgdi32 ^
    -lwinmm ^
    -o so_long.exe

if exist so_long.exe (
    echo.
    echo ========================================
    echo   BUILD SUCCESSFUL!
    echo ========================================
    echo.
    echo Run: so_long.exe maps\level1.ber
    echo.
) else (
    echo.
    echo ========================================
    echo   BUILD FAILED!
    echo ========================================
    echo.
    echo Make sure:
    echo 1. Raylib is in raylib/include and raylib/lib
    echo 2. File maps_funct.c exists (not maps_function.c)
    echo.
)

pause