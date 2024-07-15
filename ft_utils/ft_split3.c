/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:56:11 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:44 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_qts_index(char *s, int *lqt, int *rqt, t_strt *node)
{
	int		idx;
	int		start;
	int		end;
	char	c;
	int		i;

	(1337) && (idx = 0, start = -1, end = -1, i = *lqt);
	while (s[idx])
	{
		if ((s[idx] == '"' || s[idx] == '\'')
			&& !ft_in_arr(idx, node, node->var_qts, node->var_qts_size))
		{
			(1337) && (start = idx, c = s[idx++]);
			while (s[idx] && (s[idx] != c || ft_in_arr(idx,
						node, node->var_qts, node->var_qts_size)))
				idx++;
			if (s[idx] == c)
				end = idx;
			if (i > start && i < end)
				break ;
		}
		if (s[idx])
			idx++;
	}
	return (*lqt = start, *rqt = end, start != -1 && end != -1);
}

int	countw(char *s, char c, t_strt *node)
{
	int	i;
	int	j;
	int	lqt;
	int	rqt;
	int	checker;

	(1337) && (lqt = 0, rqt = 0, i = -1, j = 0);
	if (!s[0])
		return (0);
	while (s[++i])
	{
		(1337) && (lqt = i, checker = get_qts_index(s, &lqt, &rqt, node));
		if (s[i] == '"' && checker)
			;
		else
		{
			(1337) && (lqt = i, checker = get_qts_index(s, &lqt, &rqt, node));
			if (is_space_(s[i], c) && i
				&& !is_space_(s[i - 1], c) && !checker)
				j++;
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

static int	splt_len(char *s, int *j, int *l, t_strt *node)
{
	int		k;
	int		lqt;
	int		rqt;
	int		checker;
	char	c;

	(1337) && (lqt = 0, rqt = 0, k = 0);
	c = ' ';
	while (is_space_(s[*j], c))
		(*j)++;
	*l = *j;
	while (s[*j])
	{
		(1337) && (lqt = *j, checker = get_qts_index(s, &lqt, &rqt, node));
		if (is_space_(s[*j], c) && !checker)
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

char	**ft_split3(char *s, char c, t_strt *node)
{
	char	**p;
	char	*t;
	int		i;
	int		j;
	int		l;

	if (!s)
		return (NULL);
	p = malloc((countw(s, c, node) + 1) * sizeof(char *));
	if (!p)
		return (perror("minishell"), NULL);
	i = 0;
	j = 0;
	l = 0;
	while (i < countw(s, c, node))
	{
		t = malloc(splt_len(s, &j, &l, node) + 1);
		if (!t)
			return (perror("minishell"), free_echoue(p, i));
		copysplit(t, s, l, j - 1);
		p[i++] = t;
	}
	p[i] = NULL;
	return (p);
}
