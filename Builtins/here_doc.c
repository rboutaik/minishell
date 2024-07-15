/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:07:25 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/01 17:05:06 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_child_soon(t_env *env, char **line, int expandable, int fd)
{
	if (expandable)
	{
		*line = ft_expander(*line, &env, NULL, NULL);
		if (!*line)
			(free(*line), close(fd), exit(1));
	}
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	free(*line);
}

void	sec_backup(t_mini *shell)
{
	if (shell->here_doc_fd[1] != -1 && dup2(shell->here_doc_fd[1],
			STDOUT_FILENO) == -1)
	{
		perror("minishell");
		malloc_failure(shell, NULL);
		exit(1);
	}
	if (shell->here_doc_fd[0] != -1 && dup2(shell->here_doc_fd[0],
			STDIN_FILENO) == -1)
	{
		(shell->here_doc_fd[1] != -1) && (close(shell->here_doc_fd[1]));
		perror("minishell");
		malloc_failure(shell, NULL);
		exit(1);
	}
}

void	here_doc_child(t_strt *stack, int i, int fd, t_mini *shell)
{
	int		expandable;
	char	*line;

	sec_backup(shell);
	(1337) && (rl_catch_signals = 1, expandable = 0, signal(SIGINT, SIG_DFL));
	signal(SIGQUIT, SIG_IGN);
	if (stack->delemiter && find(stack->delemiter[i], "\"\'"))
	{
		stack->delemiter[i] = ft_rm_quotes(stack->delemiter[i], stack, 0);
		if (stack->delemiter[i] == NULL)
			(perror("minishell: "), exit(1));
	}
	while (fd != -1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, stack->delemiter[i]))
			break ;
		(1337) && (shell->env->i_in_ou = -1, shell->env->flag = -1);
		here_doc_child_soon(shell->env, &line, expandable, fd);
	}
	(free(line), close(fd), exit(0));
}

int	execute_here_doc_soon(t_strt *stack, int i, t_mini *shell, int *ex_stat)
{
	int		exit_status;
	int		hdrc_state;
	int		pid;
	int		fd;
	char	*name;

	(1337) && (hdrc_state = 0, exit_status = 0, name = get_name(shell));
	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 777);
	if (fd == -1)
		return (free(name),
			(custom_error(NULL, strerror(errno), "heredoc file"), -1));
	pid = fork();
	if (pid == -1)
		return (free(name), perror("minishell"), -1);
	if (pid == 0)
		here_doc_child(stack, i, fd, shell);
	(waitpid(pid, &exit_status, 0), close(fd));
	if (stack->delemiter)
		(stack->expandable = !find(stack->delemiter[i], "\"\'"));
	(1337) && (fd = open(name, O_RDONLY), stack->here_doc_fd = fd);
	(unlink(name), free(name));
	if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
		(ft_putstr_fd("\n", 2), hdrc_state = 1, *ex_stat = 1, close(fd));
	return (hdrc_state);
}

int	execute_here_doc(t_strt *stack, int *ex_stat, int i, t_mini *shell)
{
	char	*tmp;

	*ex_stat = 0;
	tmp = NULL;
	if (stack->delemiter && stack->delemiter[i][0] == '$'
		&& (stack->delemiter[i][1] == '\'' || stack->delemiter[i][1] == '"'))
	{
		tmp = ft_strdup(stack->delemiter[i] + 1);
		if (!tmp)
			return (-1);
		free(stack->delemiter[i]);
		stack->delemiter[i] = tmp;
	}
	return (execute_here_doc_soon(stack, i, shell, ex_stat));
}
