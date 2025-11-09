/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsantand <lsantand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:22:46 by lsantand          #+#    #+#             */
/*   Updated: 2025/09/26 18:20:57 by lsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int				temp;
	unsigned int	pn;

	temp = 0;
	pn = n;
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			temp = ft_putchar_fd('-', fd);
			if (temp == -1)
				return (temp);
			n = -n;
		}
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		temp = ft_putchar_fd((n % 10) + '0', fd);
		if (temp == -1)
			return (temp);
	}
	return (nb_len(pn));
}
