/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:22:44 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:22:45 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	int		rt_val;

	i = 0;
	rt_val = 0;
	if (!s)
		i = ft_putstr_fd("(null)", fd);
	else
	{
		while (s[i])
		{
			rt_val = ft_putchar_fd(s[i++], fd);
			if (rt_val == -1)
				return (rt_val);
		}
	}
	return (i);
}
