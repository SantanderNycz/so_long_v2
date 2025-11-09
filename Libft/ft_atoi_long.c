/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:34:43 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:34:46 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_pos_neg(const char *str, int *i)
{
	if (str[(*i)] == '-')
	{
		(*i)++;
		return (0);
	}
	else if (str[(*i)] == '+')
	{
		(*i)++;
		return (1);
	}
	else if ((str[(*i)] >= '0') && (str[(*i)] <= '9'))
		return (1);
	else
		return (2);
}

static void	ft_skipws(const char *str, int *i)
{
	while (((str[*(i)] > 8) & (str[*(i)] < 14)) || str[*(i)] == ' ')
		(*i)++;
}

long int	ft_atoi_long(const char *str)
{
	int			i;
	long int	num;
	int			*p_i;
	int			sign;

	i = 0;
	num = 0;
	p_i = &i;
	ft_skipws(str, p_i);
	sign = check_pos_neg(str, p_i);
	if (sign == 2)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num != ((num * 10 + (sign * (str[i] - '0'))) / 10))
			return ((long int)((sign + 1) / 2 / -1));
		num = num * 10 + (str[i] - 48);
		i++;
	}
	if (sign == 0)
		num = num * -1;
	return ((long int)num);
}
