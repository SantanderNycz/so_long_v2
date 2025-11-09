/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:27 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:23:27 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nlist;

	nlist = malloc(sizeof(t_list));
	if (!nlist)
		return (0);
	nlist->content = content;
	nlist->next = 0;
	return (nlist);
}
