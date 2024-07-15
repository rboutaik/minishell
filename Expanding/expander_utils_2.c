/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 02:30:45 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:59 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambig(char *s, t_vars2 *v, t_vars3 *v3, t_strt *p_tr)
{
	v->j = len_2d(v->tmp);
	if (v->j > 1 && p_tr && ft_strcmp(s, v3->expanded_var))
		p_tr->cmd_flag = 1;
	if (v->i != -1 && (v->j > 1 || (v->j == 0
				&& ft_strlen(s) == ft_strlen(v->exp_var))) && v3->f == 0
		&& !ft_between_dqts(s, v3->start - 1))
	{
		p_tr->ofile_flag = ft_ralloc_ofile_flag(p_tr, v3->n);
		if (!p_tr->ofile_flag)
			return (free(v->exp_var), -1);
		return (free(v->exp_var), 1);
	}
	if (v->i != -1 && (v->j > 1 || (v->j == 0
				&& ft_strlen(s) == ft_strlen(v->exp_var))) && v3->f == 1
		&& !ft_between_dqts(s, v3->start - 1))
	{
		p_tr->ifile_flag = ft_ralloc_ifile_flag(p_tr, v3->n);
		if (!p_tr->ifile_flag)
			return (free(v->exp_var), -1);
		return (free(v->exp_var), 1);
	}
	(1337) && (v->j = 0, v->sp_cnt = 0);
	while (v->echo_flag && v->var[v->i] && is_space_(v->var[v->i], ' '))
		(1337) && (v->i++, v->sp_cnt++);
	return (free(v->exp_var), v->ss = ft_strlen(v->var) - 1, 0);
}

char	*calc_words(char *s, t_vars2 *v)
{
	while (v->var[v->i])
	{
		if (v->echo_flag && is_space_(v->var[v->i], ' '))
		{
			v->i++;
			while (v->var[v->i] && is_space_(v->var[v->i], ' '))
			{
				v->i++;
				v->sp_cnt++;
			}
		}
		else
			v->i++;
	}
	v->str = malloc(sizeof(char)
			* (ft_strlen(s) - v->size + (ft_strlen(v->var)) + 1));
	if (!v->str)
		return (perror("minishell"), NULL);
	v->i = 0;
	return (s);
}

void	*bind_vars_2(t_strt *p_tr, t_vars2 *v)
{
	v->j++;
	if (p_tr && (v->var[v->j - 1] == '"'
			|| v->var[v->j - 1] == '\''))
	{
		p_tr->var_qts = ft_alloc_int_arr(p_tr, v->i + v->x);
		if (!p_tr->var_qts)
			return (NULL);
	}
	return ((void *)1337);
}

void	*bind_vars(t_strt *p_tr, t_vars2 *v, t_vars3 *v3)
{
	if (v->i == v3->start - 1)
	{
		(1337) && (v->j = 0, v->x = 0);
		while (v->echo_flag && v->var[v->j] && is_space_(v->var[v->j], ' '))
			v->j++;
		while (v->var[v->j])
		{
			v->str[v->i + v->x] = v->var[v->j];
			if (v->echo_flag && is_space_(v->var[v->j], ' '))
				while (v->var[v->j] && is_space_(v->var[v->j], ' '))
					v->j++;
			else
				if (!bind_vars_2(p_tr, v))
					return (NULL);
			v->x++;
		}
		(1337) && (v->j = v->i + v->x, v->i = v3->end);
	}
	return ((void *)1337);
}

void	exp_echo_flag(t_strt *p_tr, t_vars2 *v2, t_vars3 *v3, char *s)
{
	if (p_tr && ft_strcmp(p_tr->command, "echo")
		&& ft_strcmp(s, v3->expanded_var)
		&& !ft_strcmp(p_tr->command, s)
		&& !ft_between_dqts(s, v3->start - 1))
		v2->echo_flag = 1;
}
