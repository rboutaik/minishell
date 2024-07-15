/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exec_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:39:04 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:07 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*pipe_b_or_a(t_mini *shell, t_strt *p_stack, int fd[], int sec_in_out[])
{
	if (p_stack->prev && p_stack->prev->type == PIPE)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (perror("minishell"), malloc_failure(shell, NULL), fd);
		close(fd[0]);
		if (!p_stack->next || p_stack->next->type != PIPE)
			if (dup2(sec_in_out[1], STDOUT_FILENO) == -1)
				return (perror("minishell"), malloc_failure(shell, NULL), fd);
	}
	if (p_stack->next && p_stack->next->type == PIPE)
	{
		if (pipe(fd) == -1)
			return (perror("minishell"), malloc_failure(shell, NULL), fd);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (perror("minishell"), malloc_failure(shell, NULL), fd);
		close(fd[1]);
	}
	return (fd);
}

int	is_valid__(char *option, char **exp_opt)
{
	int		i_name;
	char	*name;

	i_name = 0;
	*exp_opt = NULL;
	while (option && option[i_name])
	{
		if (option[i_name] == '='
			|| (option[i_name] == '+' && option[i_name + 1] == '='))
			break ;
		i_name++;
	}
	name = malloc(i_name + 1);
	if (!name)
		return (perror("minishell"), 0);
	ft_strncpy(name, option, i_name);
	if (check_varname(name))
		*exp_opt = name;
	else
		free(name);
	return (1);
}

void	*env_handle__(t_strt *node, t_env *env, char **p__tr, void *p_tmp)
{
	char	*exp_opt;
	char	*cmd;

	(1337) && (exp_opt = NULL, p_tmp = (void *)1337, cmd = NULL);
	if (!p__tr)
		return (NULL);
	if (ft_strcmp(p__tr[0], "exit"))
		return (free_echoue(p__tr, len_2d(p__tr)), (void *)1337);
	else if (ft_strcmp(p__tr[0], "export")
		&& ft_strrchr(p__tr[len_2d(p__tr) - 1], '='))
	{
		if (!is_valid__(p__tr[len_2d(p__tr) - 1], &exp_opt))
			return (free_echoue(p__tr, len_2d(p__tr)), NULL);
		((!exp_opt) && (p_tmp = env_value_modifie(env, ft_strjoin("_=",
						node->option[len_2d(node->option) - 1]))))
				|| (p_tmp = env_value_modifie(env, ft_strjoin("_=", exp_opt)));
	}
	else if (node->option && node->option[len_2d(node->option) - 1][0])
		p_tmp = env_value_modifie(env, ft_strjoin("_=",
					node->option[len_2d(node->option) - 1]));
	else
		p_tmp = env_handle___soon(node, env, p_tmp);
	return (free_echoue(p__tr, len_2d(p__tr)), free(exp_opt), free(cmd), p_tmp);
}

void	close_red_fd(t_vars *v)
{
	if (v->f)
	{
		if (dup2(v->sec_in, STDIN_FILENO) == -1)
		{
			perror("minishell");
			exit(-1);
		}
		if (dup2(v->sec_out, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			close(v->sec_in);
			exit(-1);
		}
		close(v->sec_out);
		close(v->sec_in);
	}
}

void	set_exit_cmd_flag(t_strt *p_stack, int flag)
{
	while (p_stack)
	{
		(p_stack->type != CH_MD) && (p_stack->exit_cmd_flag = flag);
		p_stack = p_stack->next;
	}
}
