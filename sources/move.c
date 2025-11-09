/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:20:58 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/26 18:55:04 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	move_check(t_game *game, char direction)
{
	int	temp_i;
	int	x;
	int	y;

	find_x_y(*game, game->player_pos, &x, &y);
	temp_i = get_ind(game->player_pos, game->map, direction);
	if (temp_i == -1)
		return (-1);
	if (game->map[temp_i] == '1')
		return (0);
	if (game->map[temp_i] == 'C')
	{
		game->collect--;
		move_player(*game, game->player_pos, direction);
	}
	if (game->map[temp_i] == '0' || game->map[temp_i] == 'P')
		move_player(*game, game->player_pos, direction);
	if (game->map[temp_i] == 'E')
		move_player(*game, game->player_pos, direction);
	if (game->map[temp_i] == 'E' && game->collect == 0)
		return (close_program(game), 0);
	if (game->map[temp_i] == 'O')
		move_player(*game, game->player_pos, direction);
	game->player_pos = temp_i;
	return (game->move++, 0);
}

int	move_player(t_game game, int from_pos, char direction)
{
	int	x;
	int	y;

	find_x_y(game, from_pos, &x, &y);
	x = x * 96;
	y = y * 96;
	put_image(game, '0', x, y);
	if (game.map[from_pos] == 'C' || game.map[from_pos] == 'O')
	{
		put_image(game, 'O', x, y);
		game.map[from_pos] = 'O';
	}
	if (game.map[from_pos] == 'E')
		put_image(game, 'E', x, y);
	if (direction == 't')
		y -= 96;
	if (direction == 'b')
		y += 96;
	if (direction == 'r')
		x += 96;
	if (direction == 'l')
		x -= 96;
	ft_printf("Número de movimentos: %d\n", ++game.move);
	return (put_image(game, 'P', x, y), 0);
}
