/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_inou_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:50:48 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:54 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*fill_in_file_2(t_strt ***node, int i, char *s_str, char *old_str)
{
	int		wild_flag;
	char	**p__tr;

	p__tr = NULL;
	wild_flag = 0;
	p__tr = wild_card(s_str, **node, &wild_flag, old_str);
	if (!p__tr && wild_flag)
		return (free(s_str), NULL);
	if (p__tr && p__tr[0] && !p__tr[1])
		(**node)->in_file = ft_realloc_2d((**node)->in_file, p__tr[0]);
	else
		(**node)->in_file = ft_realloc_2d((**node)->in_file, s_str);
	if (!(**node)->in_file)
		return (free_echoue(p__tr, len_2d(p__tr)), free(s_str), NULL);
	if (p__tr && p__tr[0] && p__tr[1])
	{
		(**node)->ifile_flag = ft_ralloc_ifile_flag(**node, i);
		if (!(**node)->ifile_flag)
			return (free_echoue(p__tr, len_2d(p__tr)), free(s_str), NULL);
	}
	return (free_echoue(p__tr, len_2d(p__tr)), free(s_str), (void *)1337);
}

void	*fill_in_file(t_strt **node, char *str, t_mini *shell, char *s_str)
{
	char	**tmp;

	(1337) && (s_str = ft_strdup(str), shell->env->flag = 1);
	shell->env->i_in_ou = len_2d((*node)->in_file);
	s_str = ft_expander(s_str, &shell->env, *node, str);
	tmp = ft_split(s_str, ' ');
	if (!tmp)
		return (free(s_str), NULL);
	if (len_2d(tmp) > 1)
	{
		(1337) && (free(s_str), s_str = ft_strdup(str));
		(*node)->ifile_flag = ft_ralloc_ifile_flag((*node),
				len_2d((*node)->in_file));
		if (!(*node)->ifile_flag || !s_str)
			return (free_echoue(tmp, len_2d(tmp)), free(s_str), NULL);
	}
	if (!ft_in_arr(len_2d((*node)->in_file), *node,
			(*node)->ifile_flag, (*node)->ifile_flag_size))
	{
		s_str = ft_rm_quotes(s_str, *node, 1);
		if (!s_str)
			return (free_echoue(tmp, len_2d(tmp)), NULL);
	}
	return (free_echoue(tmp, len_2d(tmp)),
		fill_in_file_2(&node, len_2d((*node)->in_file), s_str, str));
}

void	*fill_ou_file_2(t_strt ***node, char *s_str, int i, char *str)
{
	int		wild_flag;
	char	**p__tr;

	p__tr = NULL;
	wild_flag = 0;
	p__tr = wild_card(s_str, **node, &wild_flag, str);
	if (!p__tr && wild_flag)
		return (free(s_str), NULL);
	if (p__tr && p__tr[0] && !p__tr[1])
		(**node)->ou_file = ft_realloc_2d((**node)->ou_file, p__tr[0]);
	else
		(**node)->ou_file = ft_realloc_2d((**node)->ou_file, s_str);
	if (!(**node)->ou_file)
		return (free_echoue(p__tr, len_2d(p__tr)), free(s_str), NULL);
	if (p__tr && p__tr[0] && p__tr[1])
	{
		(**node)->ofile_flag = ft_ralloc_ofile_flag(**node, i);
		if (!(**node)->ofile_flag)
			return (free_echoue(p__tr, len_2d(p__tr)), free(s_str), NULL);
	}
	return (free_echoue(p__tr, len_2d(p__tr)), free(s_str), (void *)1337);
}

void	*fill_ou_file(t_strt **node, char *str, t_mini *shell, char *s_str)
{
	char	**tmp;

	(1337) && (s_str = ft_strdup(str), shell->env->flag = 0);
	shell->env->i_in_ou = len_2d((*node)->ou_file);
	s_str = ft_expander(s_str, &shell->env, *node, str);
	tmp = ft_split(s_str, ' ');
	if (!s_str || !tmp)
		return (free(s_str), NULL);
	if (len_2d(tmp) > 1)
	{
		(1337) && (free(s_str), s_str = ft_strdup(str));
		(*node)->ofile_flag = ft_ralloc_ofile_flag((*node),
				len_2d((*node)->ou_file));
		if (!(*node)->ofile_flag || !s_str)
			return (free(s_str), free_echoue(tmp, len_2d(tmp)), NULL);
	}
	if (!ft_in_arr(len_2d((*node)->ou_file), *node,
			(*node)->ofile_flag, (*node)->ofile_flag_size))
	{
		s_str = ft_rm_quotes(s_str, *node, 1);
		if (!s_str)
			return (free_echoue(tmp, len_2d(tmp)), NULL);
	}
	return (free_echoue(tmp, len_2d(tmp)),
		fill_ou_file_2(&node, s_str, len_2d((*node)->ou_file), str));
}
