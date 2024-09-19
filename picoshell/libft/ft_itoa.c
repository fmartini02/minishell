/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmartini <fmartini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:38:32 by fmartini          #+#    #+#             */
/*   Updated: 2024/01/27 22:38:32 by fmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(long int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa2(long int n, int len, int neg)
{
	char	*res;

	res = malloc(len + 1);
	res[len] = '\0';
	len--;
	if (neg)
	{
		res[0] = '-';
		while (len > 0)
		{
			res[len] = (n % 10) + 48;
			n /= 10;
			len--;
		}
	}
	else
	{
		while (len >= 0)
		{
			res[len] = (n % 10) + 48;
			n /= 10;
			len--;
		}
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		neg;
	int		len;
	long	temp;

	neg = 0;
	temp = n;
	if (n == 0)
	{
		res = malloc(2);
		res[0] = '0';
		res[1] = '\0';
	}
	else
	{
		len = ft_len(temp);
		if (n < 0)
		{
			neg = 1;
			temp *= -1;
			len++;
		}
		res = ft_itoa2(temp, len, neg);
	}
	return (res);
}
