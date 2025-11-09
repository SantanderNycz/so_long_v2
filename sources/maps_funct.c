#include "../includes/so_long.h"
#include <stdio.h>

int get_map_size(t_game *game, char *filename)
{
    FILE *file = fopen(filename, "r");
    int size = 0;
    int c;

    if (!file)
        return ft_printf_e(ER_NOMAP), close_program(game), 0;

    while ((c = fgetc(file)) != EOF)
        size++;

    fclose(file);
    return size;
}

int get_map(t_game *game, char *file)
{
    FILE *fp = fopen(file, "r");
    int c;
    int i = 0;

    if (!fp)
        return ft_printf_e(ER_NOMAP), close_program(game), 0;

    while ((c = fgetc(fp)) != EOF)
    {
        game->map[i++] = (char)c;
    }

    fclose(fp);
    return 0;
}
