/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_and_opt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:51:24 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:53 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*cmd_from_exp(t_strt ***node, char **p__str, int i__str)
{
	if ((**node)->command == NULL)
		(**node)->command = ft_strdup(p__str[0]);
	else
		i__str--;
	if (!(**node)->command)
		return (free_echoue(p__str, len_2d(p__str)), NULL);
	while (p__str[i__str])
	{
		(**node)->option = ft_realloc_2d((**node)->option,
				p__str[i__str++]);
		if (!(**node)->option)
			return (free_echoue(p__str, len_2d(p__str)), NULL);
	}
	return ((void *)1337);
}

void	*fill_cmd_type_2(t_strt ***node, char **p__str, char *s_str, int i__str)
{
	if (p__str)
	{
		if (cmd_from_exp(node, p__str, i__str) == NULL)
			return (NULL);
	}
	else
	{
		if ((**node)->command != NULL)
		{
			(**node)->option = ft_realloc_2d((**node)->option,
					s_str);
			if (!(**node)->option)
				return (free_echoue(p__str, len_2d(p__str)), NULL);
		}
		else
			(**node)->command = ft_strdup(s_str);
		if (!(**node)->command)
			return (free_echoue(p__str, len_2d(p__str)), NULL);
	}
	(**node)->type = CMD;
	(**node)->pr_exec = ft_realloc_arr(**node, CMD);
	if (!(**node)->pr_exec)
		return (free_echoue(p__str, len_2d(p__str)), NULL);
	return (free_echoue(p__str, len_2d(p__str)),
		(**node)->pr_exec);
}

void	*fill_cmd_type(t_strt **node, char *str, t_mini *shell, int i)
{
	int		wild_flag;
	char	**p__str;
	char	**m_str;
	char	*s_str;

	s_str = init_vars(node, &wild_flag, shell, str);
	if (!s_str)
		return (NULL);
	m_str = ft_split3(s_str, ' ', *node);
	free(s_str);
	if (!m_str)
		return (NULL);
	while (m_str[++i])
	{
		(1337) && (p__str = NULL, wild_flag = 0);
		p__str = wild_card(m_str[i], *node, &wild_flag, str);
		if (!p__str && wild_flag)
			return (free_echoue(m_str, len_2d(m_str)), NULL);
		if (!fill_cmd_type_2(&node, p__str, m_str[i], 1))
			return (free_echoue(m_str, len_2d(m_str)), NULL);
	}
	return (free_echoue(m_str, len_2d(m_str)), (void *)1337);
}

void	*fill_opt_2(t_strt ***node, char **p__tr, char *s_str)
{
	int	i__str;

	i__str = 0;
	if (p__tr)
	{
		while (p__tr[i__str])
		{
			(**node)->option = ft_realloc_2d((**node)->option, p__tr[i__str++]);
			if (!(**node)->option)
				return (free_echoue(p__tr, len_2d(p__tr)), NULL);
		}
	}
	else
	{
		(**node)->option = ft_realloc_2d((**node)->option, s_str);
		if (!(**node)->option)
			return (free_echoue(p__tr, len_2d(p__tr)), NULL);
	}
	return (free_echoue(p__tr, len_2d(p__tr)), (void *)1337);
}

void	*fill_opt(t_strt **node, char *str, t_mini *shell, int i)
{
	int		wild_flag;
	char	**p__tr;
	char	**m_str;
	char	*s_str;

	s_str = init_vars(node, &wild_flag, shell, str);
	m_str = ft_split(s_str, ' ');
	free(s_str);
	if (!m_str)
		return (NULL);
	while (m_str[++i])
	{
		(1337) && (p__tr = NULL, wild_flag = 0);
		m_str[i] = ft_rm_quotes(m_str[i], *node, 0);
		if (!m_str[i])
			return (NULL);
		p__tr = wild_card(m_str[i], *node, &wild_flag, str);
		if (!p__tr && wild_flag)
			return (free_echoue(m_str, len_2d(m_str)), NULL);
		if (fill_opt_2(&node, p__tr, m_str[i]) == 0)
			return (free_echoue(m_str, len_2d(m_str)), NULL);
	}
	return (free_echoue(m_str, len_2d(m_str)), (void *)1337);
}
