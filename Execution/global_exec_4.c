/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exec_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 15:49:30 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:05 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_strt	*ft_lstlast(t_strt *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_remove_node(t_strt **stack, t_strt *node)
{
	t_strt	*p_tmp;

	if (!node)
		return ;
	if (!node->prev)
	{
		p_tmp = *stack;
		*stack = (*stack)->next;
		p_tmp->next = NULL;
		if (*stack)
			(*stack)->prev = NULL;
		free(p_tmp);
	}
	else
	{
		node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		free(node);
	}
}

t_strt	*cp_node2(t_strt *node, t_strt *p_node)
{
	p_node->delemiter = node->delemiter;
	node->delemiter = NULL;
	p_node->append = node->append;
	node->append = NULL;
	p_node->in_file = node->in_file;
	node->in_file = NULL;
	p_node->ou_file = node->ou_file;
	node->ou_file = NULL;
	p_node->chil_cmd = NULL;
	p_node->next = NULL;
	p_node->cmd_flag = node->cmd_flag;
	p_node->ofile_flag = node->ofile_flag;
	p_node->ifile_flag = node->ifile_flag;
	p_node->ofile_flag_size = node->ofile_flag_size;
	p_node->ifile_flag_size = node->ifile_flag_size;
	p_node->var_qts = node->var_qts;
	p_node->var_qts_size = node->var_qts_size;
	p_node->opt_flag = node->opt_flag;
	p_node->var_qts_dejavu = node->var_qts_dejavu;
	return (p_node);
}

t_strt	*cp_node(t_strt *node)
{
	t_strt	*p_node;

	p_node = ft_lstnew(node->str, ft_strlen(node->str) + 1);
	p_node->command = malloc(ft_strlen(node->command) + 1);
	if (!p_node->command)
		return (free(p_node->str), free(p_node), perror("minishell"), NULL);
	ft_strncpy(p_node->command, node->command, ft_strlen(node->command));
	p_node->pr_exec = node->pr_exec;
	node->pr_exec = NULL;
	p_node->pr_exec_size = node->pr_exec_size;
	p_node->type = node->type;
	p_node->here_doc_fd = node->here_doc_fd;
	node->here_doc_fd = -1;
	p_node->option = node->option;
	p_node->redirect = node->redirect;
	node->redirect = NULL;
	p_node->here_doc = node->here_doc;
	return (node->option = NULL, node->here_doc = NULL, cp_node2(node, p_node));
}

void	executer_start(t_mini *shell)
{
	int		lst_cmd_exec;
	int		exit_status;
	t_strt	*p_stack;
	char	*tmp;

	(1337) && (exit_status = 0, lst_cmd_exec = 1,
	p_stack = shell->stack);
	set_exit_cmd_flag(p_stack, 0);
	ft_dup_sec(shell);
	exit_status = hrd_ex(shell, p_stack, 0);
	if (!exit_status)
		exit_status = recursion_func(shell, p_stack, lst_cmd_exec, &p_stack);
	(close(shell->here_doc_fd[0]), close(shell->here_doc_fd[1]));
	if (p_stack->type != CH_MD && (!p_stack->prev || (p_stack->prev
				&& p_stack->prev->type != PIPE)) && !env_handle__(p_stack,
			shell->env, ft_split(p_stack->str, ' '), NULL))
		malloc_failure(shell, NULL);
	else if (p_stack->prev && p_stack->prev->type == PIPE
		&& !env_value_modifie(shell->env, ft_strdup("_=")))
		malloc_failure(shell, NULL);
	tmp = ft_itoa(exit_status);
	(!tmp) && (malloc_failure(shell, NULL));
	if (env_value_modifie(shell->env, ft_strjoin("?=", tmp)) == NULL)
		(free(tmp), malloc_failure(shell, NULL));
	free(tmp);
}
