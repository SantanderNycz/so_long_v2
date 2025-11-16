@echo off
echo ========================================
echo     SO_LONG - Windows Compilation
echo ========================================
echo.

REM Verificar se obj existe, se não criar
if not exist obj mkdir obj

REM Compilar cada arquivo .c
echo [1/10] Compiling animation.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/animation.c -o obj/animation.o

echo [2/10] Compiling check_solvability.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/check_solvability.c -o obj/check_solvability.o

echo [3/10] Compiling check.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/check.c -o obj/check.o

echo [4/10] Compiling enemy_funct.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/enemy_funct.c -o obj/enemy_funct.o

echo [5/10] Compiling imgs.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/imgs.c -o obj/imgs.o

echo [6/10] Compiling maps_function.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/maps_funct.c -o obj/maps_funct.o

echo [7/10] Compiling move.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/move.c -o obj/move.o

echo [8/10] Compiling render.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/render.c -o obj/render.o

echo [9/10] Compiling so_long.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/so_long.c -o obj/so_long.o

echo [10/10] Compiling utils.c...
gcc -Wall -Wextra -O2 -std=c99 -I./includes -Iraylib/include -c sources/utils.c -o obj/utils.o

echo.
echo Linking executable...
gcc obj/animation.o obj/check_solvability.o obj/check.o obj/enemy_funct.o obj/imgs.o obj/maps_funct.o obj/move.o obj/render.o obj/so_long.o obj/utils.o -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm -o so_long.exe

if exist so_long.exe (
    echo.
    echo ========================================
    echo   BUILD SUCCESSFUL!
    echo ========================================
    echo.
    echo To run the game, type:
    echo    so_long.exe maps\level1.ber
    echo.
) else (
    echo.
    echo ========================================
    echo   BUILD FAILED!
    echo ========================================
    echo Check the errors above.
)

pause