/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:23:29 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/15 17:23:29 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	new_list = 0;
	if (!f || !del || !lst)
		return (0);
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		ft_lstadd_back(&new_list, new_elem);
		if (!new_list)
		{
			ft_lstclear(&new_list, del);
			return (0);
		}
		lst = lst->next;
	}
	return (new_list);
}
