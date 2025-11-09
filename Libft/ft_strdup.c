/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:22:35 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:22:37 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	i;
	char	*copy;

	i = 0;
	len = ft_strlen(str);
	copy = malloc(sizeof(char) * (len + 1));
	if (copy == 0)
		return (0);
	while (str[i] && i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}
