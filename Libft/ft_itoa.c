/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:46 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:23:47 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*value;
	unsigned int	nn;
	int				len;

	nn = n;
	len = nb_len(nn);
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (0);
	value[len] = 0;
	if (n < 0)
		nn = -n;
	while (--len >= 0)
	{
		if (len == 0 && n < 0)
			value[0] = '-';
		else
			value[len] = nn % 10 + '0';
		nn = nn / 10;
	}
	return (value);
}
