/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:17:49 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:19:21 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/so_long.h"

int	nb_occurrence(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count);
}

int	line_len(char *str)
{
	int	i;

	i = 0;
	while (str[i++])
		if (str[i - 1] == '\n')
			return (i - 1);
	return (i);
}

int	get_ind(int pos, char *map, char directions)
{
	int	line_l;

	line_l = line_len(map) + 1;
	if (pos > 0 && map[pos] == '\n')
		return (-1);
	if (directions == 't')
		if (pos > line_l)
			return (pos - line_l);
	if (directions == 'b')
		if (pos > 0 && pos < (int)ft_strlen(map))
			return (pos + line_l);
	if (directions == 'l')
		if (pos - 1 > 0 && map[pos - 1] != '\n')
			return (pos - 1);
	if (directions == 'r')
		if (map[pos + 1] && map[pos + 1] != '\n')
			return (pos + 1);
	return (-1);
}

int	find_index(char *map, char to_find)
{
	int	i;

	i = 0;
	while (map[i] && map[i] != to_find)
		i++;
	if (map[i] == to_find)
		return (i);
	return (-1);
}

int	find_x_y(t_game game, int pos, int *x, int *y)
{
	int	i;

	i = 0;
	*x = 0;
	*y = 0;
	while (game.map[i] && i < pos)
	{
		if (game.map[i] == '\n')
		{
			*y = *y + 1;
			*x = 0;
		}
		else
			*x = *x + 1;
		i++;
	}
	return (0);
}
