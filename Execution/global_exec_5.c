/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exec_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:57:13 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:06 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shunt_free_stack(t_strt *stack)
{
	t_strt	*p_stack;

	p_stack = NULL;
	while (stack)
	{
		if (stack->type != ACCOL)
		{
			p_stack = stack->next;
			free(stack->command);
			free(stack->str);
			free(stack);
		}
		else
		{
			free(stack->str);
			free(stack->command);
			free(stack->pr_exec);
			p_stack = stack->next;
			free(stack);
		}
		stack = p_stack;
	}
}

void	executer_convert_soon(t_mini *shell, t_strt **p_stack,
		t_strt **stack, int *accol_count)
{
	t_strt	*p_tmp;

	p_tmp = ft_lstnew(NULL, 0);
	if (!p_tmp)
		malloc_failure(shell, NULL);
	p_tmp->type = CH_MD;
	ft_lstadd_back(p_stack, p_tmp);
	ft_lstlast(*p_stack)->chil_cmd = executer_convert(shell,
		(*stack)->next);
	*stack = (*stack)->next;
	*stack = accol_checker(*stack, accol_count);
}

t_strt	*executer_convert(t_mini *shell, t_strt *stack)
{
	int		accol_count;
	t_strt	*pstack_2;
	t_strt	*p_stack;
	t_strt	*p_tmp;

	(1337) && (p_stack = NULL, pstack_2 = stack);
	while (stack)
	{
		accol_count = 0;
		if (stack->str[0] == '(')
			executer_convert_soon(shell, &p_stack, &stack, &accol_count);
		else if (stack->str[0] != ')')
		{
			p_tmp = cp_node(stack);
			if (!p_tmp)
				return (free_stack(p_stack, NULL),
					malloc_failure(shell, NULL), NULL);
			ft_lstadd_back(&p_stack, p_tmp);
		}
		else
			return (p_stack);
		if (stack)
			stack = stack->next;
	}
	return (shunt_free_stack(pstack_2), p_stack);
}

int	cmd_ignore(t_strt **p_stack, int *lst_cmd_exec, int exit_status)
{
	if ((*p_stack)->prev && (((*p_stack)->prev->type == AND
				&& exit_status != 0) || ((*p_stack)->prev->type == OR
				&& exit_status == 0) || ((*p_stack)->prev->type == PIPE
				&& (*lst_cmd_exec == 0))))
	{
		(*p_stack) = (*p_stack)->next;
		while ((*p_stack) && (*p_stack)->type >= 2 && (*p_stack)->type <= 4)
			(*p_stack) = (*p_stack)->next;
		(*lst_cmd_exec) = 0;
		return (1);
	}
	return (0);
}

int	redir_after(t_strt **p_stack, t_vars *v, int *exit_status, t_mini *shell)
{
	vars_init(v);
	if ((*p_stack)->next && ((*p_stack)->next->type == APPEND
			|| (*p_stack)->next->type == REDIR))
	{
		(exp_caller(shell, (*p_stack)->next), v->i_dice_1--);
		(*exit_status) = file_with_cmd((*p_stack)->next, v, shell, 0);
		if ((*exit_status))
		{
			(*p_stack) = (*p_stack)->next;
			(*p_stack) = (*p_stack)->next;
			if (*p_stack)
				(*p_stack) = (*p_stack)->next;
			return (shell->exit_s = (*exit_status), 1);
		}
		if (!buitins_dup((*p_stack)->next, v, 1, shell))
			malloc_failure(shell, NULL);
	}
	return (0);
}
