/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:22:26 by ohw               #+#    #+#             */
/*   Updated: 2021/11/26 15:12:02 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(long n, int fd)
{
	char	c;

	if (n == 0)
		return ;
	print(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	n2;

	n2 = (long)n;
	if (n2 == 0)
		write(fd, "0", 1);
	else if (n2 < 0)
	{
		write(fd, "-", 1);
		print(-n2, fd);
	}
	else
		print(n2, fd);
}
