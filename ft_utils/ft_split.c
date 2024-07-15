/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:53:54 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:47 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space_(int a, int c)
{
	if (c == 32)
	{
		if (a == 32 || (a >= 9 && a <= 13))
			return (1);
	}
	else if (c == a)
		return (1);
	return (0);
}

static int	countw(char *s, char c)
{
	int	i;
	int	j;

	(1337) && (i = 0, j = 0);
	if (!s[0])
		return (0);
	while (s[i])
	{
		if (s[i] == '"' && ft_check_qts(s, i))
		{
			while (s[i] != '"')
				i++;
			i++;
		}
		else
		{
			if (is_space_(s[i], c) && i
				&& !is_space_(s[i - 1], c) && !ft_check_qts(s, i))
				j++;
			i++;
		}
	}
	if (!is_space_(s[i - 1], c))
		j++;
	return (j);
}

static void	copysplit(char *d, char *s, int i, int j)
{
	int	k;

	k = 0;
	while (i < j)
		d[k++] = s[i++];
	d[k] = '\0';
}

static int	splt_len(char *s, int *j, int *l, char c)
{
	int	k;

	k = 0;
	while (is_space_(s[*j], c))
		(*j)++;
	*l = *j;
	while (s[*j])
	{
		if (is_space_(s[*j], c) && !ft_check_qts(s, *j))
		{
			(*j)++;
			break ;
		}
		k++;
		(*j)++;
	}
	if (!s[*j] && !is_space_(s[(*j) - 1], c))
		(*j)++;
	return (k);
}

char	**ft_split(char *s, char c)
{
	char	**p;
	char	*t;
	int		i;
	int		j;
	int		l;

	if (!s)
		return (NULL);
	p = malloc((countw(s, c) + 1) * sizeof(char *));
	if (!p)
		return (perror("minishell"), NULL);
	i = 0;
	j = 0;
	l = 0;
	while (i < countw(s, c))
	{
		t = malloc(splt_len(s, &j, &l, c) + 1);
		if (!t)
			return (perror("minishell"), free_echoue(p, i));
		copysplit(t, s, l, j - 1);
		p[i++] = t;
	}
	p[i] = 0;
	return (p);
}
