/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:04:19 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/01 17:46:57 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_options(t_strt *stack, t_mini *shell)
{
	char	**options;
	char	**tmp;
	int		size;
	int		i;
	int		j;

	(1337) && (tmp = NULL, size = 0, j = 1, i = 0);
	size = len_2d(stack->option);
	if (cmd_extend(stack, &j, &tmp) == NULL)
		malloc_failure(shell, tmp);
	options = ft_get_options(stack, shell, tmp, j);
	while (++i < j)
	{
		options[i] = ft_strdup(tmp[i]);
		if (!options[i])
			return (free_echoue(options, i), malloc_failure(shell, tmp), NULL);
	}
	(free_echoue(tmp, len_2d(tmp)), --i);
	while (++i < size + 1 + (j - 1))
	{
		options[i] = ft_strdup(stack->option[i - j]);
		if (!options[i])
			return (free_echoue(options, i), malloc_failure(shell, tmp), NULL);
	}
	return (options[i] = NULL, options);
}

int	ft_is_wild(char *str, t_strt *node)
{
	int		i;
	int		j;
	int		sp;
	char	c;

	(1337) && (i = 0, sp = -1, i = 0);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"')
			&& !ft_in_arr(i, node, node->var_qts, node->var_qts_size))
		{
			(1337) && (c = str[i++], j = i);
			while (str[j] && str[j] != c)
				if (str[j++] == '*')
					sp = j - 1;
			if (str[j] == c && (sp >= i && sp < j))
				return (0);
		}
		if (str[i])
			i++;
	}
	if (sp == -1 && !ft_strrchr(str, '*'))
		return (0);
	return (1);
}

int	wild_checker(char *str, char *wild, int *i, int *j)
{
	while (str[*i] && str[*i] == '*')
		(*i)++;
	while (wild[*j] && str[*i] != wild[*j])
		(*j)++;
	if (str[*i] && !str[*i + 1] && wild[ft_strlen(wild) - 1] == str[*i])
		return (1);
	if (!str[*i] && !wild[*j])
		return (1);
	if (!str[*i] || !wild[*j] || str[*i] != wild[*j])
		return (0);
	return (2);
}

int	is_match(char *str, char *wild, char *old_str, int flag)
{
	int	i;
	int	j;
	int	i_dice;

	(1337) && (i = 0, j = 0, i_dice = 0);
	while (str[i])
	{
		if (str[i] == '*')
		{
			i_dice += (i_dice != 0);
			while (old_str[i_dice] && old_str[i_dice] != '*')
				i_dice++;
		}
		if (str[i] == '*' && !ft_between_sqts(old_str, i_dice)
			&& !ft_between_dqts(old_str, i_dice))
		{
			flag = wild_checker(str, wild, &i, &j);
			if (flag != 2)
				return (flag);
		}
		else if (str[i] != wild[j])
			return (0);
		(1337) && (i += (str[i] != '\0'), j++);
	}
	return ((str[i] == wild[j]));
}

char	**wild_card(char *str, t_strt *p_tr, int *wild_card, char *old_str)
{
	DIR				*directory;
	struct dirent	*entry;
	char			**res;

	res = NULL;
	directory = opendir(".");
	if (!directory)
		return (*wild_card = 1, NULL);
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (((entry->d_name[0] == '.' && str[0] == '.')
				|| (entry->d_name[0] != '.' && str[0] != '.'))
			&& is_match(str, entry->d_name, old_str, 0))
		{
			res = ft_realloc_2d(res, entry->d_name);
			if (!res)
				return (*wild_card = 1, closedir(directory), NULL);
		}
		entry = readdir(directory);
	}
	closedir(directory);
	p_tr->opt_flag = 1;
	return (ft_sort_2d(res), res);
}
