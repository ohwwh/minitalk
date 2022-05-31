/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:41:44 by hoh               #+#    #+#             */
/*   Updated: 2021/11/30 20:28:34 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getbuf(int n, int base)
{
	int	buf;

	buf = 1;
	if (n <= 0)
	{	
		buf ++;
		n *= -1;
	}
	while (n)
	{
		n /= base;
		buf ++;
	}
	return (buf);
}

static char	*body(long temp, int base, int capital)
{
	int		buf;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (buf = getbuf(temp, base)));
	if (ret)
	{
		ret[(buf--) - 1] = 0;
		while (temp)
		{
			if (temp % 10 >= 10 && !capital)
				ret[(buf--) - 1] = temp % base + 87;
			else if (temp % 10 >= 10 && capital)
				ret[(buf--) - 1] = temp % base + 55;
			else
				ret[(buf--) - 1] = temp % base + '0';
			temp /= base;
		}
	}
	return (ret);
}

char	*ft_itoa_base(int n, int base, int capital)
{
	long	temp;
	char	*ret;

	if (n >= 0)
		temp = n;
	else
		temp = -(long)n;
	ret = body(temp, base, capital);
	if (ret)
	{
		if (n < 0)
			ret[0] = '-';
		else if (n == 0)
			ret[0] = '0';
	}
	return (ret);
}
