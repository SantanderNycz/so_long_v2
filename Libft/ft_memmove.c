/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:12 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:23:13 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (dest > src)
	{
		i = n;
		while (--i < n)
			((char *)dest)[i] = ((char *)src)[i];
	}
	if (src > dest)
		while (++i < n)
			((char *)dest)[i] = ((char *)src)[i];
	return (dest);
}
