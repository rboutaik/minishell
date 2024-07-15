/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:22:19 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:37 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_here_doc(t_strt *node, t_env *env, t_mini *shell)
{
	int		hrdc_stat;
	int		i_stack;
	int		ex_stat;
	t_strt	*p_stack;

	(1337) && (hrdc_stat = 0, p_stack = shell->stack);
	while (p_stack && p_stack != node)
	{
		i_stack = 0;
		while (p_stack->here_doc && p_stack->here_doc[i_stack])
		{
			hrdc_stat = execute_here_doc(p_stack, &ex_stat,
					i_stack++, shell);
			close(p_stack->here_doc_fd);
			if (hrdc_stat)
			{
				if (hrdc_stat == 1)
					if (!env_value_modifie(env, ft_strdup("?=1")))
						return (-1);
				return (hrdc_stat);
			}
		}
		p_stack = p_stack->next;
	}
	return (0);
}

int	parser_2(t_strt *node, t_mini *shell, int hrdc_flag, int hrdc_state)
{
	if (node->type >= 2 && node->type <= 4 && node->next
		&& ((node->next->type == node->type || node->next->str[0] == ')')
			|| (node->next->type >= 2 && node->next->type <= 4)))
		return (parser_err_synt((node->next)->str, hrdc_flag), (!hrdc_flag)
			&& (hrdc_state = parser_here_doc(node, shell->env,
					shell)), hrdc_state);
	else if (node->str[0] == '(' && node->next && node->next->type >= 2
		&& node->next->type <= 4)
		return (parser_err_synt(node->next->str, hrdc_flag), (!hrdc_flag)
			&& (hrdc_state = parser_here_doc(node, shell->env,
					shell)), hrdc_state);
	else
	{
		hrdc_state = parser_accol(shell, node, 0, hrdc_flag);
		if (node->type == ACCOL && hrdc_state != 1337)
			return (hrdc_state);
		else if (node->str[0] == ')' && node->next && node->next->type == CMD
			&& node->next->command)
			return (hrdc_state = 0, (!hrdc_flag) && (hrdc_state
					= parser_here_doc(node->next->next, shell->env, shell),
					(hrdc_state != 1) && (parser_err_synt(node->next->command,
							1))), hrdc_state);
	}
	return (1337);
}

int	parser_1(t_strt *node, t_mini *shell, int hrdc_flag, int hrdc_stat)
{
	char	**p__tr;
	int		tmp;

	p__tr = ft_split2(node->str, node->delem_2);
	if (!p__tr)
		return (-1);
	tmp = parser_sq_dq_red_app_herd(node, p__tr, hrdc_flag, shell);
	if (tmp != 1337)
		return (free_echoue(p__tr, len_2d(p__tr)), tmp);
	else if ((node->type == CMD || node->type == REDIR
			|| node->type == APPEND || node->type == HERE_DOC)
		&& node->next && node->next->next && node->next->str[0] == '(')
	{
		if (node->option || node->redirect || node->here_doc || node->append)
			return ((!hrdc_flag) && (hrdc_stat
					= parser_here_doc(node->next, shell->env, shell),
					(hrdc_stat != 1) && (parser_err_synt("(", 1))),
				free_echoue(p__tr, len_2d(p__tr)), hrdc_stat);
		return (parser_error_after_accol(shell, node, p__tr, hrdc_flag));
	}
	else if (!node->next && node->type >= 2 && node->type <= 4)
		return ((!hrdc_flag) && ((hrdc_stat = parser_here_doc(node, shell->env,
						shell)), (hrdc_stat != 1) && (parser_err_synt(node->str,
						1))), free_echoue(p__tr, len_2d(p__tr)), hrdc_stat);
	return (free_echoue(p__tr, len_2d(p__tr)), 1337);
}

int	parser_phase(t_mini *shell, int hrdc_flag)
{
	int		hrdc_stat;
	t_strt	*p_stack;
	char	**p__tr;

	(1337) && (p__tr = NULL, hrdc_stat = 0,
	p_stack = shell->stack, parser_accol(shell, p_stack, 1, hrdc_flag));
	if (p_stack->type >= 2 && p_stack->type <= 4)
		return (parser_err_synt(p_stack->str, hrdc_flag), 0);
	while (p_stack)
	{
		hrdc_stat = parser_1(p_stack, shell, hrdc_flag, 0);
		if (hrdc_stat != 1337)
			return (hrdc_stat);
		hrdc_stat = parser_2(p_stack, shell, hrdc_flag, 0);
		if (hrdc_stat != 1337)
			return (hrdc_stat);
		p_stack = p_stack->next;
	}
	return (1337);
}
