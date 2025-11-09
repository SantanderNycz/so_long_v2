/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:22:07 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:22:07 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (needle[j] == haystack[i + j] && (i + j < len))
		{
			j++;
			if (!needle[j])
				return (&((char *)haystack)[i]);
		}
		i++;
	}
	return (0);
}
