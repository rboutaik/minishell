/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sq_dq_red_app_herd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:57:04 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:34 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_sq_dq(char **p__tr, int *i__dice, int hrdc_flag, char **q_err)
{
	char	quote[2];
	int		indice__tmp;

	*q_err = ft_strdup(p__tr[*i__dice]);
	ft_strncpy(quote, p__tr[(*i__dice)++], 1);
	while (p__tr[*i__dice] && !ft_strcmp(p__tr[*i__dice], quote))
		(*i__dice)++;
	if (!p__tr[*i__dice])
		return (0);
	else
	{
		indice__tmp = *i__dice;
		indice__tmp++;
		while (p__tr[indice__tmp] && !ft_strcmp(p__tr[indice__tmp], "'")
			&& !ft_strcmp(p__tr[indice__tmp], "\""))
			indice__tmp++;
		if (p__tr[indice__tmp])
			return (free(*q_err), *q_err = p__tr[indice__tmp],
				parser_sq_dq(p__tr, &indice__tmp, hrdc_flag, q_err));
		else
			return (free(*q_err), 1337);
	}
	return (1337);
}

int	parser_spc_err_set(t_mini *shell, t_strt *node, char **p__tr, int i__dice)
{
	int	hrdc_state;

	hrdc_state = 0;
	if (node->next && !p__tr[i__dice + 1])
	{
		parser_err_synt(node->next->str, 1);
		hrdc_state = parser_spc_err(shell, node, p__tr, i__dice);
	}
	else if ((!p__tr[i__dice + 1]
			|| ft_is_delm(p__tr[i__dice + 1], node->delem_2) > 0)
		&& *p__tr[i__dice] != '\'' && *p__tr[i__dice] != '\"')
	{
		hrdc_state = parser_spc_err(shell, node, p__tr, i__dice);
		(hrdc_state != 1) && (parser_err_synt(NULL, 1));
	}
	return (hrdc_state);
}

int	parser_sq_dq_red_app_herd_soon(t_strt *node, int hrdc_flag, int i__dice,
	t_mini *shell)
{
	char	**p__tr;
	int		hrdc_state;

	hrdc_state = 0;
	p__tr = ft_split2(node->str, node->delem_2);
	if (!p__tr)
		return (-1);
	if (node->next && !p__tr[i__dice + 1])
		return ((!hrdc_flag) && (hrdc_state
				= parser_spc_err_set(shell, node, p__tr, i__dice)),
			free_echoue(p__tr, len_2d(p__tr)), hrdc_state);
	else if ((!p__tr[i__dice + 1]
			|| ft_is_delm(p__tr[i__dice + 1], node->delem_2) > 0)
		&& *p__tr[i__dice] != '\'' && *p__tr[i__dice] != '\"')
	{
		if (!p__tr[i__dice + 1])
			return ((!hrdc_flag) && (hrdc_state
					= parser_spc_err_set(shell, node, p__tr, i__dice)),
				free_echoue(p__tr, len_2d(p__tr)), hrdc_state);
		else if (*p__tr[i__dice + 1] != '\'' && *p__tr[i__dice + 1] != '"')
			return ((!hrdc_flag) && (parser_err_synt(p__tr[i__dice + 1], 1),
					hrdc_state = parser_spc_err(shell, node, p__tr, i__dice)),
				free_echoue(p__tr, len_2d(p__tr)), hrdc_state);
	}
	return (free_echoue(p__tr, len_2d(p__tr)), 1337);
}

int	parser_spc_sq_dq(t_mini *shell, t_strt *node, char **p__tr, int i__dice)
{
	int	hdrc_count;
	int	hrdc_stat;
	int	tmp;

	hrdc_stat = 0;
	tmp = i__dice - 2;
	hdrc_count = 0;
	while (tmp >= 0)
		if (ft_strcmp(p__tr[tmp--], "<<"))
			hdrc_count++;
	hrdc_stat = parser_spc_err(shell, node, node->here_doc, hdrc_count
			- (ft_is_delm((ft_strrchr(node->str, *p__tr[i__dice])
						- (i__dice > 0)), node->delem_2) < 0));
	return (hrdc_stat);
}

int	parser_sq_dq_red_app_herd(t_strt *node, char **p__tr, int hrdc_flag,
	t_mini *shell)
{
	int		hrdc_st;
	int		i__dice;
	char	*q_er;
	int		tmp;

	(1337) && (i__dice = -1, hrdc_st = 0);
	while (p__tr[++i__dice])
	{
		if (*p__tr[i__dice] == '\'' || *p__tr[i__dice] == '\"')
		{
			(1337) && (tmp = i__dice, q_er = NULL);
			if (!parser_sq_dq(p__tr, &i__dice, hrdc_flag, &q_er))
				return ((!hrdc_flag) && (hrdc_st = parser_spc_sq_dq(shell,
							node, p__tr, tmp)), (hrdc_st != 1)
					&& (parser_err_synt(q_er, hrdc_flag)), free(q_er), hrdc_st);
		}
		else if (ft_is_delm(p__tr[i__dice], node->delem_2) > 0)
		{
			tmp = parser_sq_dq_red_app_herd_soon(node,
					hrdc_flag, i__dice, shell);
			if (tmp != 1337)
				return (tmp);
		}
	}
	return (1337);
}
