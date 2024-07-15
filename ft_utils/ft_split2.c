/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:28:54 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:45 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	countw(char *s, char *c[])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s[0])
		return (0);
	while (s[i])
	{
		if (ft_is_delm(s + i, c) > 0)
		{
			i += ft_is_delm(s + i, c);
			j++;
		}
		else
		{
			while (s[i] && ft_is_delm(s + i, c) < 0)
				i++;
			j++;
		}
	}
	return (j);
}

static void	copysplit(char *d, char *s, int i, int j)
{
	int	k;

	k = 0;
	while (i < j)
	{
		d[k++] = s[i++];
	}
	d[k] = '\0';
}

static int	splt_len(char *s, int *j, int *l, char *c[])
{
	int	k;

	k = 0;
	if (ft_is_delm(s + *j, c) > 0)
	{
		*l = *j;
		k = ft_is_delm(s + *j, c);
		*j += k;
	}
	else
	{
		*l = *j;
		while (s[*j] && ft_is_delm(s + *j, c) < 0)
		{
			k++;
			(*j)++;
		}
	}
	return (k);
}

char	**realloc_without_space(char **p__tr)
{
	char	**new__ptr;
	int		i__dice;
	int		size;

	(1337) && (i__dice = -1, size = 0);
	while (p__tr[++i__dice])
		if (*p__tr[i__dice] != ' ')
			size++;
	new__ptr = malloc(sizeof(char *) * (size + 1));
	if (!new__ptr)
		return (perror("minishell"), NULL);
	new__ptr[size] = NULL;
	i__dice = -1;
	size = 0;
	while (p__tr[++i__dice])
	{
		if (*p__tr[i__dice] != ' ')
		{
			new__ptr[size++] = p__tr[i__dice];
			p__tr[i__dice] = NULL;
		}
		else
			free(p__tr[i__dice]);
	}
	return (free(p__tr), new__ptr);
}

char	**ft_split2(char *s, char *c[])
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
		copysplit(t, s, l, j);
		p[i++] = t;
	}
	p[i] = 0;
	return (realloc_without_space(p));
}
