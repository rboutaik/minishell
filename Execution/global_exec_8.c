/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exec_8.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:15:59 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:08 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_with_pipe_bef_soon(t_vars4 *v, int sec_in_out[], int *lst_cmd_exec,
		int *exit_status)
{
	if (dup2(v->fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell");
		malloc_failure(v->shell, NULL);
	}
	close(v->fd[0]);
	v->shell->pipe_fd[1] = v->fd[1];
	v->shell->pipe_fd[2] = 1;
	if (dup2(sec_in_out[1], STDOUT_FILENO) == -1)
	{
		perror("minishell");
		malloc_failure(v->shell, NULL);
	}
	*exit_status = executer_phase(v->shell, v->p_stack, IN_CHILD);
	*lst_cmd_exec = 1;
}

void	cmd_w_pipe_wait(struct termios *attr, int *exit_status, int *flag)
{
	while (waitpid(-1, exit_status, 0) != -1)
		*flag = 1;
	if (WIFSIGNALED(*exit_status) && WTERMSIG(*exit_status) == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		*exit_status = 130;
		*flag = 0;
	}
	if (WIFSIGNALED(*exit_status) && WTERMSIG(*exit_status) == SIGQUIT)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, attr);
		printf("Quit : 3\n");
		*exit_status = 131;
		*flag = 0;
	}
}

void	sec_in_out_init(t_mini *shell, int sec_in_out[3], int lst_cmd_exec)
{
	shell->pipe_fd[2] = -1;
	sec_in_out[0] = dup(STDIN_FILENO);
	sec_in_out[1] = dup(STDOUT_FILENO);
	if (sec_in_out[0] == -1 || sec_in_out[1] == -1)
	{
		(sec_in_out[0] != -1) && (close(sec_in_out[0]));
		perror("minishell");
		malloc_failure(shell, NULL);
	}
	shell->sec_fd[0] = sec_in_out[0];
	shell->sec_fd[1] = sec_in_out[1];
	sec_in_out[2] = lst_cmd_exec;
}

void	exp_caller(t_mini *shell, t_strt *p_stack)
{
	char	**str;

	(1337) && (free(p_stack->command), p_stack->command = NULL);
	(1337) && (free(p_stack->pr_exec), p_stack->pr_exec = NULL);
	(1337) && (p_stack->pr_exec_size = 0), free(p_stack->ifile_flag);
	(1337) && (p_stack->ifile_flag = NULL, p_stack->ifile_flag_size = 0);
	(1337) && (free(p_stack->ofile_flag), p_stack->ofile_flag = NULL);
	(1337) && (p_stack->ofile_flag_size = 0), free(p_stack->var_qts);
	(1337) && (p_stack->var_qts = NULL, p_stack->var_qts_size = 0);
	p_stack->var_qts_dejavu = 0;
	free_echoue(p_stack->option, len_2d(p_stack->option));
	free_echoue(p_stack->in_file, len_2d(p_stack->in_file));
	(1337) && (p_stack->option = NULL, p_stack->in_file = NULL);
	free_echoue(p_stack->ou_file, len_2d(p_stack->ou_file));
	free_echoue(p_stack->redirect, len_2d(p_stack->redirect));
	(1337) && (p_stack->ou_file = NULL, p_stack->redirect = NULL);
	free_echoue(p_stack->here_doc, len_2d(p_stack->here_doc));
	free_echoue(p_stack->delemiter, len_2d(p_stack->delemiter));
	(1337) && (p_stack->here_doc = NULL, p_stack->delemiter = NULL);
	free_echoue(p_stack->append, len_2d(p_stack->append));
	(1337) && (p_stack->append = NULL, str = ft_split(p_stack->str, ' '));
	if (!str || !fill_compare(shell, p_stack, p_stack->delem_1, str))
		malloc_failure(shell, str);
	ft_decal_value(p_stack->pr_exec, p_stack->pr_exec_size, CMD);
	free_echoue(str, len_2d(str));
}

char	*init_vars(t_strt **node, int *wild_flag, t_mini *shell, char *str)
{
	char	*s_str;

	*wild_flag = 0;
	shell->env->i_in_ou = -1;
	shell->env->flag = -1;
	s_str = ft_strdup(str);
	s_str = ft_expander(s_str, &shell->env, *node, str);
	return (s_str);
}
