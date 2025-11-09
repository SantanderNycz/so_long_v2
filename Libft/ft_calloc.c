/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:24:03 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:24:04 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*var;

	if (size && count > 2147483647 / size)
		return (0);
	var = malloc(count * size);
	if (!var)
		return (0);
	ft_bzero(var, count * size);
	return (var);
}
