/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_accol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:31:16 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:36 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parser_accol_1(t_strt *stack, t_strt **pstack__1, t_strt **pstack__2,
	int *cl_acol)
{
	*pstack__2 = NULL;
	if (!*pstack__1 && !*cl_acol)
		*pstack__1 = stack;
	while (*pstack__1 && (*pstack__1)->str[0] != ')')
		*pstack__1 = (*pstack__1)->next;
	if (*pstack__1)
		return (*pstack__1 = (*pstack__1)->next, *cl_acol = 1, 1337);
	return (0);
}

int	parser_accol_2(t_strt *stack, t_strt **pstack__1, t_strt **pstack__2,
	int *op_acol)
{
	*pstack__1 = NULL;
	if (!(*op_acol)++)
		*pstack__2 = stack->prev;
	while (*pstack__2 && (*pstack__2)->str[0] != '(')
		*pstack__2 = (*pstack__2)->prev;
	if (*pstack__2 && (*pstack__2)->str[0] == '(')
		return (*pstack__2 = (*pstack__2)->prev, 1337);
	return (0);
}

int	parser_accol_err(t_strt *node, t_mini *shell, int hrdc_flag, int flag_err)
{
	int		hdrc_state;
	char	*str_err;

	hdrc_state = 0;
	((!flag_err) && (str_err = node->next->str)) ||
	((flag_err == 1) && (str_err = NULL)) ||
	((flag_err == 2) && (str_err = node->str));
	if (flag_err && (node->type == ACCOL
			|| (node->here_doc && node->delemiter)))
		return ((!hrdc_flag) && (hdrc_state
				= parser_here_doc(node, shell->env, shell),
				(hdrc_state != 1) && (parser_err_synt(str_err, 1))),
			hdrc_state);
	else
		return (parser_err_synt(str_err, hrdc_flag), (!hrdc_flag)
			&& (hdrc_state = parser_here_doc(node, shell->env,
					shell)), hdrc_state);
	return (0);
}

int	parser_accol(t_mini *shell, t_strt *stack, int static_flag, int hrdc_flag)
{
	static t_strt	*pstack_1;
	static t_strt	*pstack_2;
	static int		op_acol;
	static int		cl_acol;
	int				synt_st;

	if (static_flag)
		return (pstack_1 = NULL, pstack_2 = NULL, cl_acol = 0, op_acol = 0, 1);
	if (stack->next && stack->type == 6 && stack->next->type == 6
		&& stack->str[0] != stack->next->str[0])
		return (parser_accol_err(stack, shell, hrdc_flag, 0));
	if (stack->str[0] == '(')
	{
		synt_st = parser_accol_1(stack, &pstack_1, &pstack_2, &cl_acol);
		return (op_acol = 0, (!synt_st) && (synt_st = parser_accol_err(stack,
					shell, hrdc_flag, 1)), synt_st);
	}
	else if (stack->str[0] == ')')
	{
		synt_st = parser_accol_2(stack, &pstack_1, &pstack_2, &op_acol);
		return (cl_acol = 0, (!synt_st) && (synt_st = parser_accol_err(stack,
					shell, hrdc_flag, 2)), synt_st);
	}
	return (0);
}
