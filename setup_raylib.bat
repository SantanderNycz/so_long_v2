@echo off
echo ========================================
echo     SO_LONG - Raylib Setup
echo ========================================
echo.
echo This script will download Raylib for Windows
echo.

REM Criar pasta raylib se não existir
if not exist raylib mkdir raylib
cd raylib

echo Downloading Raylib...
echo.
echo IMPORTANT: You need to manually download Raylib from:
echo https://github.com/raysan5/raylib/releases
echo.
echo Look for: raylib-5.0_win64_mingw-w64.zip
echo.
echo After downloading:
echo 1. Extract the ZIP file
echo 2. Copy the 'include' and 'lib' folders to: %cd%
echo.
echo Your folder structure should be:
echo raylib/
echo   - include/
echo       - raylib.h
echo   - lib/
echo       - libraylib.a
echo.
echo Press any key when you're done...
pause > nul

cd ..

REM Verificar se raylib foi instalado
if exist "raylib\include\raylib.h" (
    if exist "raylib\lib\libraylib.a" (
        echo.
        echo ========================================
        echo   Raylib detected! Setup complete.
        echo ========================================
        echo.
        echo Now you can compile by running:
        echo    compile.bat
        echo.
    ) else (
        echo.
        echo ERROR: raylib\lib\libraylib.a not found!
        echo Please make sure you extracted the lib folder correctly.
    )
) else (
    echo.
    echo ERROR: raylib\include\raylib.h not found!
    echo Please make sure you extracted the include folder correctly.
)

pause