/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exec_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:35:32 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:04 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	func_caller_dup_sec(t_strt *node, t_vars *v, t_mini *shell)
{
	if (is_build_in(node, shell) && (node->in_file || node->ou_file))
	{
		if (dup2(v->sec_in, STDIN_FILENO) == -1)
		{
			perror("minishell");
			malloc_failure(shell, NULL);
		}
		if (dup2(v->sec_out, STDOUT_FILENO) == -1)
		{
			close(v->sec_in);
			perror("minishell");
			malloc_failure(shell, NULL);
		}
		(close(v->sec_in), close(v->sec_out));
	}
}

void	func_caller(t_strt *node, t_vars *v, int exit_cmd_flag, t_mini *shell)
{
	char	*cmd;

	cmd = ft_strdup(node->command);
	if (cmd && is_build_in(node, shell))
		cmd = ft_rm_quotes(cmd, node, 0);
	((!cmd) && (malloc_failure(shell, NULL))) || (node->var_qts_dejavu = 0);
	if (ft_strcmp(cmd, "env"))
		v->exit_status = build_env(&shell->env, shell);
	else if (ft_strcmp(cmd, "exit"))
		v->exit_status = builtin_exit(shell, node->option, exit_cmd_flag);
	else if (ft_strcmp(cmd, "export"))
		v->exit_status = build_export(&shell->env, node->option, shell);
	else if (ft_strcmp(cmd, "unset"))
		v->exit_status = build_unset(&shell->env, node->option);
	else if (ft_strcmp(cmd, "cd"))
		v->exit_status = builtin_cd(node, shell->env, shell);
	else if (ft_strcmp(cmd, "pwd"))
		v->exit_status = builtin_pwd(shell->secure_pwd);
	else if (ft_strcmp(cmd, "echo"))
		v->exit_status = builtin_echo(node);
	else
		v->exit_status = exec_cmd(node, shell, v->fd_in, v->fd_out);
	free(cmd);
	func_caller_dup_sec(node, v, shell);
}

void	wait_and_close(t_mini *shell, t_vars *v)
{
	if (v->pid == 0)
		exit (EXIT_SUCCESS);
	if (v->pid != -10 && v->pid != 0)
		waitpid(v->pid, &v->exit_status, 0);
	(v->fd_in) && (close(v->fd_in));
	if (v->fd_out != 1)
		close(v->fd_out);
	if (WEXITSTATUS(v->exit_status) == 255)
		malloc_failure(shell, NULL);
}

int	builtin_execve(t_mini *shell, t_strt *node, int in_child)
{
	t_vars	v;

	vars_init(&v);
	if (in_child && is_build_in(node, shell))
	{
		v.pid = fork();
		if (v.pid == -1)
			return (perror("minishell"), malloc_failure(shell, NULL), 0);
	}
	while (v.i_dice_1 < node->pr_exec_size && (v.pid == -10 || v.pid == 0))
	{
		if (node->pr_exec[v.i_dice_1] == CMD)
		{
			if (file_with_cmd(node, &v, shell, 0) == 1)
				return (1);
			if (buitins_dup(node, &v, 0, shell) == -1)
				malloc_failure(shell, NULL);
			func_caller(node, &v, node->exit_cmd_flag, shell);
		}
		else if (file_without_cmd(node, &v) == 1)
			return (1);
	}
	wait_and_close(shell, &v);
	return (v.exit_status);
}

t_strt	*accol_checker(t_strt *stack, int *accol_count)
{
	while (stack)
	{
		if (stack->str[0] == '(')
			(*accol_count)++;
		else if (stack->str[0] == ')' && !*accol_count)
			break ;
		else if (stack->str[0] == ')')
			(*accol_count)--;
		stack = stack->next;
	}
	return (stack);
}
