/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 06:35:12 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:49 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(const char *str)
{
	int				i;
	int				signe;
	long			nb;
	unsigned long	x;

	i = 0;
	signe = 1;
	x = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			signe *= -1;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = x * 10 + str[i++] - 48;
		x = nb;
		if (x > 9223372036854775807 && signe == 1)
			return (1338);
		else if (x > 9223372036854775808uL && signe == -1)
			return (1338);
	}
	return (x * signe);
}

static int	ft_size(int n)
{
	int		i;
	long	x;

	i = 0;
	if (n < 0)
	{
		x = (long)n * (-1);
		i = 1;
	}
	else
		x = n;
	while (x > 0)
	{
		x /= 10;
		i++;
	}
	return (i);
}

static long	ft_signe(int n)
{
	long	x;

	if (n < 0)
		x = (long)n * -1;
	else
		x = n;
	return (x);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	x;
	int		size;

	if (n == 0)
		return (ft_strdup("0"));
	size = ft_size(n);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (perror("minishell"), NULL);
	x = ft_signe(n);
	i = 1;
	while (x > 0)
	{
		str[size - i++] = x % 10 + '0';
		x /= 10;
	}
	str[size] = '\0';
	if (n < 0)
		str[0] = '-';
	return (str);
}

int	ft_calc(int n)
{
	if (n < 0)
		return (0);
	return (n);
}
