/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:23:14 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:22 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_bool = 0;

void	main_sigint(int signal)
{
	int	status;

	if (signal == SIGINT)
	{
		if (waitpid(-1, &status, WNOHANG) == 0)
			return ;
		g_bool = SIGINT;
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	main_d(t_mini shell)
{
	char	*exit_status_name;
	int		exit_status_val;

	write(2, "exit\n", 6);
	exit_status_name = ft_get_from_env(&shell.env, ft_strdup("?"));
	exit_status_val = ft_atoi(exit_status_name);
	free(shell.secure_pwd);
	free(exit_status_name);
	free_env(shell.env);
	exit(exit_status_val);
}

void	parse_err(t_mini *shell, int hrdc_state)
{
	if (!hrdc_state)
	{
		if (!env_value_modifie(shell->env, ft_strdup("?=258")))
			malloc_failure(shell, NULL);
	}
	else if (hrdc_state == -1)
		malloc_failure(shell, NULL);
}

int	main_prog(t_mini *shell, char *cmd)
{
	int	hrdc_state;

	if (cmd && *cmd)
	{
		shell->here_doc_fd[0] = -1;
		shell->here_doc_fd[1] = -1;
		add_history(cmd);
		shell->stack = token_phase(cmd);
		(free(cmd), cmd = NULL);
		if (!shell->stack)
			return (free_shell(shell), 1);
		if (!fill_phase(shell))
			return (free_shell(shell), 1);
		parser_phase(shell, 1);
		hrdc_state = parser_phase(shell, 0);
		if (hrdc_state != 1337)
			parse_err(shell, hrdc_state);
		else
		{
			shell->stack = executer_convert(shell, shell->stack);
			executer_start(shell);
		}
		free_stack(shell->stack, NULL);
	}
	return (free(cmd), 0);
}

int	main(int ac, char *av[], char **env)
{
	t_mini	shell;
	char	*cmd;

	(void)ac, (void)av;
	rl_catch_signals = 0;
	(1337) && (shell.stack = NULL, shell.env = env_init(env));
	shell.secure_pwd = getcwd(NULL, 0);
	signal(SIGINT, main_sigint);
	signal(SIGQUIT, main_sigint);
	while (1337)
	{
		(1337) && (shell.sec_fd[0] = -1, shell.sec_fd[1] = -1);
		cmd = readline("minishell-1337.42$ ");
		if (g_bool == SIGINT)
		{
			if (!env_value_modifie(shell.env, ft_strdup("?=1")))
				return (255);
			g_bool = 0;
		}
		if (!cmd)
			main_d(shell);
		if (main_prog(&shell, cmd))
			return (255);
	}
	return (0);
}
