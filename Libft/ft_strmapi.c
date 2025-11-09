/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:22:14 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:22:15 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dup;

	if (!s || !f)
		return (0);
	i = -1;
	dup = ft_strdup(s);
	if (!dup)
		return (0);
	while (dup[++i])
		dup[i] = (*f)(i, dup[i]);
	return (dup);
}
