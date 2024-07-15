/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exec_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:49:55 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:06 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_strt	*ch_md(t_strt *p_stack, t_mini *shell, int fd[], int sec_in_out[])
{
	int		exit_status;
	int		pid;
	t_vars	v;

	fd = pipe_b_or_a(shell, p_stack, fd, sec_in_out);
	if (redir_after(&p_stack, &v, &exit_status, shell))
		return (p_stack);
	pid = fork();
	if (pid == -1)
		return (perror("minishell"), malloc_failure(shell, NULL), NULL);
	if (pid == 0)
		return (set_exit_cmd_flag(p_stack->chil_cmd, 1),
			exit_status = recursion_func(shell, p_stack->chil_cmd,
				sec_in_out[2], NULL), exit(exit_status), NULL);
	(close_red_fd(&v), waitpid(pid, &exit_status, 0));
	exit_status = WEXITSTATUS(exit_status);
	(exit_status == 255) && malloc_failure(shell, NULL);
	(1337) && (shell->exit_s = exit_status, p_stack = p_stack->next);
	while (p_stack && ((p_stack->type >= 2 && p_stack->type <= 4)
			|| (p_stack->type == APPEND || p_stack->type == REDIR)))
		p_stack = p_stack->next;
	return ((v.sec_in != -1) && (close(v.sec_in)),
		(v.sec_out != -1) && (close(v.sec_out)), p_stack);
}

int	cmd_with_pipe_bef(t_vars4 *v, int sec_in_out[], int *lst_cmd_exec)
{
	int	exit_status;

	exit_status = 0;
	v->p_stack->exit_cmd_flag = 1;
	if (v->p_stack->next && v->p_stack->next->type == PIPE)
	{
		if (dup2(v->fd[0], STDIN_FILENO) == -1)
			return (perror("minishell"), malloc_failure(v->shell, NULL), -1);
		close(v->fd[0]);
		if (pipe(v->fd) == -1)
			return (perror("minishell"), malloc_failure(v->shell, NULL), -1);
		if (dup2(v->fd[1], STDOUT_FILENO) == -1)
			return (perror("minishell"), malloc_failure(v->shell, NULL), -1);
		close(v->fd[1]);
		v->shell->pipe_fd[0] = v->fd[0];
		v->shell->pipe_fd[2] = 0;
		exit_status = executer_phase(v->shell, v->p_stack, IN_CHILD);
		(*lst_cmd_exec) = 1;
	}
	else
		cmd_with_pipe_bef_soon(v, sec_in_out, lst_cmd_exec, &exit_status);
	return (exit_status);
}

int	cmd_with_pipe_aft(t_vars4 *v, int *lst_cmd_exec)
{
	int	exit_status;

	exit_status = 0;
	if (pipe(v->fd) == -1 || dup2(v->fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell");
		malloc_failure(v->shell, NULL);
	}
	close(v->fd[1]);
	v->shell->pipe_fd[0] = v->fd[0];
	v->shell->pipe_fd[2] = 0;
	v->p_stack->exit_cmd_flag = 1;
	exit_status = executer_phase(v->shell, v->p_stack, IN_CHILD);
	(*lst_cmd_exec) = 1;
	return (exit_status);
}

int	prt_md(t_strt *p_stack, t_vars4 *v, int sec_in_out[], int *lst_cmd_exec)
{
	int				exit_status;
	struct termios	attr;
	int				flag;

	flag = 0;
	tcgetattr(STDIN_FILENO, &attr);
	if (p_stack->prev && p_stack->prev->type == PIPE)
		exit_status = cmd_with_pipe_bef(v, sec_in_out, lst_cmd_exec);
	else if ((p_stack->next && p_stack->next->type == PIPE))
		exit_status = cmd_with_pipe_aft(v, lst_cmd_exec);
	else
	{
		exit_status = executer_phase(v->shell, p_stack, NOT_IN_CHILD);
		*lst_cmd_exec = 1;
	}
	sec_close(v->shell, sec_in_out);
	if ((!p_stack->next || p_stack->next->type != PIPE))
	{
		cmd_w_pipe_wait(&attr, &exit_status, &flag);
		(flag == 1) && (exit_status = WEXITSTATUS(exit_status));
	}
	return (exit_status);
}

int	recursion_func(t_mini *shell, t_strt *p_stack, int lst_cmd_exec,
			t_strt **lst_cmd)
{
	int		sec_in_out[3];
	int		stat;
	t_vars4	v;

	vars_init4(&v, &stat, shell);
	while (p_stack)
	{
		exp_caller(shell, p_stack);
		sec_in_out_init(shell, sec_in_out, lst_cmd_exec);
		if (cmd_ignore(&p_stack, &lst_cmd_exec, stat) == 1)
			continue ;
		if (p_stack->type == CH_MD)
		{
			p_stack = ch_md(p_stack, shell, v.fd, sec_in_out);
			(sec_close(shell, sec_in_out), stat = shell->exit_s);
			continue ;
		}
		(1337) && (v.p_stack = p_stack), ((lst_cmd) && (*lst_cmd = p_stack),
			stat = prt_md(p_stack, &v, sec_in_out, &lst_cmd_exec)),
			(p_stack = p_stack->next);
		while (p_stack && p_stack->type >= 2 && p_stack->type <= 4)
			p_stack = p_stack->next;
	}
	return ((v.fd[0] != -1) && (close(v.fd[0])), (v.fd[1] != -1)
		&& (close(v.fd[1])), close(sec_in_out[0]), close(sec_in_out[1]), stat);
}
