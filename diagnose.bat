@echo off
cls
echo ========================================
echo     SO_LONG - Diagnostic Tool
echo ========================================
echo.

set "errors=0"
set "warnings=0"

REM ===== 1. Verificar GCC =====
echo [1/8] Checking GCC...
where gcc >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo [OK] GCC found
    gcc --version | findstr /C:"gcc"
) else (
    echo [ERROR] GCC not found!
    echo         1. Install MSYS2 from https://www.msys2.org/
    echo         2. Run: pacman -S mingw-w64-x86_64-gcc
    echo         3. Add C:\msys64\mingw64\bin to PATH
    set /a errors+=1
)
echo.

REM ===== 2. Verificar Raylib Header =====
echo [2/8] Checking Raylib header...
if exist "raylib\include\raylib.h" (
    echo [OK] raylib.h found
) else (
    echo [ERROR] raylib\include\raylib.h NOT found!
    echo         1. Download from https://github.com/raysan5/raylib/releases
    echo         2. Extract and copy include/ to raylib/include/
    set /a errors+=1
)
echo.

REM ===== 3. Verificar Raylib Library =====
echo [3/8] Checking Raylib library...
if exist "raylib\lib\libraylib.a" (
    echo [OK] libraylib.a found
) else (
    echo [ERROR] raylib\lib\libraylib.a NOT found!
    echo         1. Download from https://github.com/raysan5/raylib/releases
    echo         2. Extract and copy lib/ to raylib/lib/
    set /a errors+=1
)
echo.

REM ===== 4. Verificar Header do Projeto =====
echo [4/8] Checking project header...
if exist "includes\so_long.h" (
    echo [OK] so_long.h found
) else (
    echo [ERROR] includes\so_long.h NOT found!
    set /a errors+=1
)
echo.

REM ===== 5. Verificar Arquivos Fonte =====
echo [5/8] Checking source files...
set "missing=0"

for %%f in (animation check check_solvability enemy_funct imgs move render so_long utils) do (
    if exist "sources\%%f.c" (
        echo [OK] %%f.c
    ) else (
        echo [ERROR] %%f.c NOT found!
        set /a missing+=1
        set /a errors+=1
    )
)

REM Verificar maps_funct.c vs maps_function.c
if exist "sources\maps_funct.c" (
    echo [OK] maps_funct.c
) else (
    if exist "sources\maps_function.c" (
        echo [WARNING] Found maps_function.c but need maps_funct.c
        echo           Rename: maps_function.c -^> maps_funct.c
        set /a warnings+=1
        set /a errors+=1
    ) else (
        echo [ERROR] maps_funct.c NOT found!
        set /a errors+=1
    )
)
echo.

REM ===== 6. Verificar Mapas =====
echo [6/8] Checking maps...
if not exist "maps" (
    echo [WARNING] maps\ folder not found
    echo           Create it and add level1.ber
    set /a warnings+=1
) else (
    if exist "maps\level1.ber" (
        echo [OK] level1.ber found
    ) else (
        echo [WARNING] level1.ber not found
        echo           Game will need a map file to run
        set /a warnings+=1
    )
)
echo.

REM ===== 7. Testar Compilação de Header =====
echo [7/8] Testing header compilation...
echo #include "so_long.h" > test_header.c
echo int main(void) { return 0; } >> test_header.c

gcc -E test_header.c -I./includes -I./raylib/include >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo [OK] Header compiles successfully
) else (
    echo [ERROR] Header compilation failed!
    echo         Run: gcc -E test_header.c -I./includes -I./raylib/include
    echo         to see detailed errors
    set /a errors+=1
)
del test_header.c >nul 2>nul
echo.

REM ===== 8. Verificar Script de Build =====
echo [8/8] Checking build script...
if exist "build_simple.bat" (
    echo [OK] build_simple.bat found
) else (
    echo [WARNING] build_simple.bat not found
    echo           Create it or use manual compilation
    set /a warnings+=1
)
echo.

REM ===== RESUMO =====
echo ========================================
if %errors% EQU 0 (
    if %warnings% EQU 0 (
        echo   ALL CHECKS PASSED!
        echo ========================================
        echo.
        echo Everything looks good!
        echo You can now run: build_simple.bat
    ) else (
        echo   WARNINGS FOUND: %warnings%
        echo ========================================
        echo.
        echo Your setup should work, but check warnings above.
        echo You can try running: build_simple.bat
    )
) else (
    echo   ERRORS FOUND: %errors%
    if %warnings% GTR 0 (
        echo   WARNINGS FOUND: %warnings%
    )
    echo ========================================
    echo.
    echo Please fix the errors above before compiling.
    echo.
    echo Common fixes:
    echo 1. Install MSYS2 and add to PATH
    echo 2. Download Raylib and place in raylib\ folder
    echo 3. Rename maps_function.c to maps_funct.c if needed
    echo.
    echo See INSTALL_WINDOWS.md for detailed instructions.
)
echo.

pause