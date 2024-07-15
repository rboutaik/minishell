/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:40:06 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:35 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_spc_err_2(t_mini *shell)
{
	int	hdrc_state;
	int	ex_stat;
	int	i_h_d;

	i_h_d = 0;
	ex_stat = 0;
	hdrc_state = 0;
	while (shell->stack->here_doc && shell->stack->here_doc[i_h_d])
	{
		hdrc_state = execute_here_doc(shell->stack, &ex_stat, i_h_d++, shell);
		close(shell->stack->here_doc_fd);
		if (hdrc_state)
		{
			if (hdrc_state == 1)
				if (!env_value_modifie(shell->env, ft_strdup("?=1")))
					return (-1);
			return (hdrc_state);
		}
	}
	return (1337);
}

int	parser_spc_err_1(t_mini *shell, t_strt *node, char **p__tr, int p__dice)
{
	int	hdrc_state;
	int	ex_stat;
	int	i__dice;
	int	i_h_d;

	i_h_d = 0;
	ex_stat = 0;
	i__dice = -1;
	hdrc_state = 0;
	while (++i__dice < p__dice)
	{
		if (ft_strcmp(p__tr[i__dice], "<<"))
		{
			hdrc_state = execute_here_doc(node, &ex_stat, i_h_d++, shell);
			close(node->here_doc_fd);
			if (hdrc_state)
			{
				if (hdrc_state == 1)
					if (!env_value_modifie(shell->env, ft_strdup("?=1")))
						return (-1);
				return (hdrc_state);
			}
		}
	}
	return (hdrc_state);
}

int	parser_spc_err(t_mini *shell, t_strt *node, char **p__tr, int p__dice)
{
	int	hdrc_state;

	hdrc_state = 0;
	while (shell->stack)
	{
		if (shell->stack == node)
			return (parser_spc_err_1(shell, node, p__tr, p__dice));
		else
		{
			hdrc_state = parser_spc_err_2(shell);
			if (hdrc_state != 1337)
				return (hdrc_state);
		}
		shell->stack = shell->stack->next;
	}
	return (0);
}

void	*parser_err_synt(char *str, int hrdc_flag)
{
	if (hrdc_flag)
	{
		write (2, "minishell: syntax error near unexpected token `", 48);
		if (!str)
			write (2, "newline", 8);
		else
			write (2, str, ft_strlen(str));
		write (2, "'\n", 2);
	}
	return ((void *)1337);
}

int	parser_error_after_accol(t_mini *shell, t_strt *node, char **p__tr,
								int hrdc_flag)
{
	free_echoue(p__tr, len_2d(p__tr));
	if (hrdc_flag)
	{
		p__tr = ft_split2(node->next->next->str, node->delem_2);
		if (!p__tr)
			return (-1);
		parser_err_synt(p__tr[0], 1);
		free_echoue(p__tr, len_2d(p__tr));
	}
	else
	{
		hrdc_flag = parser_here_doc(node, shell->env, shell);
		return (hrdc_flag);
	}
	return (0);
}
