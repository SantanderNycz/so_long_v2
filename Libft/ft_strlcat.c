/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:22:23 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:22:24 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	if ((!src || !dst) && size == 0)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len < size - 1 && size > 0)
	{
		while (src[i] && dst_len + i < size - 1)
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = 0;
	}
	if (dst_len > size)
		dst_len = size;
	return (dst_len + src_len);
}
