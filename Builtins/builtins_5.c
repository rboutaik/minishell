/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:26:05 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:00:57 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_caller(t_mini *shell, t_strt *stack, t_env **env)
{
	char	**cmds;
	char	*path;

	(1337) && (path = NULL, cmds = NULL);
	if (stack->cmd_flag)
	{
		cmds = ft_split(stack->command, ' ');
		if (!cmds)
			return (malloc_failure(shell, NULL), NULL);
		if (stack->var_qts_dejavu != 1)
			cmds[0] = ft_rm_quotes(cmds[0], stack, 1);
		if (!cmds[0])
			return (malloc_failure(shell, cmds), NULL);
		path = get_path(env, cmds[0]);
		free_echoue(cmds, len_2d(cmds));
	}
	else
	{
		if (stack->var_qts_dejavu != 1)
			stack->command = ft_rm_quotes(stack->command, stack, 1);
		if (!stack->command)
			return (malloc_failure(shell, cmds), NULL);
		path = get_path(env, stack->command);
	}
	return (path);
}

void	call_child_init(t_strt *stack, t_mini *shell, char ***opt, char **path)
{
	*path = get_path_caller(shell, stack, &shell->env);
	*opt = get_options(stack, shell);
	(shell->sec_fd[0] != -1) && (close(shell->sec_fd[0]));
	(shell->sec_fd[1] != -1) && (close(shell->sec_fd[1]));
	if (shell->pipe_fd[2] == 1)
		close(shell->pipe_fd[1]);
	if (shell->pipe_fd[2] == 0)
		close(shell->pipe_fd[0]);
}

void	no_path(t_strt *stack, t_mini *shell)
{
	int			i_cmd;
	char		*cmd;
	struct stat	buf;

	if (*stack->command && stack->command[ft_strlen(stack->command) - 1] == '/')
	{
		cmd = ft_strdup(stack->command);
		if (!cmd)
			malloc_failure(shell, NULL);
		i_cmd = ft_strlen(cmd) - 1;
		while (i_cmd > 0 && cmd[i_cmd] == '/')
			cmd[i_cmd--] = '\0';
		stat(stack->command, &buf);
		if (access(cmd, F_OK) == 0 && !S_ISDIR(buf.st_mode))
			(custom_error(NULL, "Not a directory", stack->command),
				free(cmd), exit(126));
		free(cmd);
		custom_error(NULL, "No such file or directory", stack->command);
	}
	else if (*stack->command && ft_strrchr(stack->command, '/'))
		custom_error(NULL, "No such file or directory", stack->command);
	else
		custom_error(NULL, "command not found", stack->command);
	exit(127);
}

void	call_child(t_strt *stack, t_mini *shell, int fd_in, int fd_out)
{
	char		**m_env;
	char		**opt;
	char		*path;
	struct stat	buf;

	call_child_init(stack, shell, &opt, &path);
	if (!path)
		no_path(stack, shell);
	if (stat(stack->command, &buf) == 0 && S_ISDIR(buf.st_mode))
		(custom_error(NULL, "is a directory", stack->command), exit(126));
	(1337) && (m_env = env_to_char(&shell->env));
	if (m_env == NULL || close2(fd_in, fd_out) == 1)
		(free(path), malloc_failure(shell, opt));
	if (access(path, X_OK) == -1)
		(custom_error(NULL, "Permission denied", path), exit(126));
	if (execve(path, opt, m_env) == -1)
		(perror("minishell: "),
			free_echoue(opt, len_2d(opt)), free(path), exit(EXIT_FAILURE));
}

int	exec_cmd(t_strt *stack, t_mini *shell, int fd_in, int fd_out)
{
	int				exit_status;
	pid_t			pid;

	exit_status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		malloc_failure(shell, NULL);
	}
	if (pid == 0)
		call_child(stack, shell, fd_in, fd_out);
	return (exit_status);
}
