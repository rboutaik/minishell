/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:31:02 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:48 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_stack(t_strt *stack, t_strt *p_stack)
{
	while (stack)
	{
		p_stack = stack->next;
		if (stack->type == CH_MD)
		{
			free_stack(stack->chil_cmd, NULL);
			(free(stack->str), free(stack));
		}
		else
		{
			free(stack->str);
			(free(stack->command), free(stack->pr_exec));
			free_echoue(stack->option, len_2d(stack->option));
			free_echoue(stack->redirect, len_2d(stack->redirect));
			free_echoue(stack->here_doc, len_2d(stack->here_doc));
			free_echoue(stack->delemiter, len_2d(stack->delemiter));
			free_echoue(stack->append, len_2d(stack->append));
			free_echoue(stack->in_file, len_2d(stack->in_file));
			free_echoue(stack->ou_file, len_2d(stack->ou_file));
			(free(stack->ofile_flag), free(stack->ifile_flag));
			(stack->here_doc_fd != -1) && (close(stack->here_doc_fd));
			(free(stack->var_qts), free(stack));
		}
		stack = p_stack;
	}
}

void	free_env(t_env *env)
{
	t_env	*p_env;

	while (env)
	{
		p_env = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = p_env;
	}
}

void	free_shell(t_mini *shell)
{
	free_stack(shell->stack, NULL);
	free(shell->secure_pwd);
	free_env(shell->env);
}

void	ft_dup_sec(t_mini *shell)
{
	shell->here_doc_fd[0] = dup(STDIN_FILENO);
	if (shell->here_doc_fd[0] == -1)
	{
		perror("minishell");
		malloc_failure(shell, NULL);
	}
	shell->here_doc_fd[1] = dup(STDOUT_FILENO);
	if (shell->here_doc_fd[1] == -1)
	{
		perror("minishell");
		malloc_failure(shell, NULL);
	}
}

void	*check_for_space(t_vars2 *v, t_vars3 *v3, char *s)
{
	char	*tmp;

	tmp = ft_strdup(v->var);
	if (!tmp)
		return (NULL);
	while (v->echo_flag && v->ss > 0 && v->var[v->ss] == ' ')
		v->var[v->ss--] = '\0';
	if (v3->new_line)
	{
		if (!ft_between_dqts(s, v3->start - 1))
		{
			free(v->var);
			v->var = ft_strjoin(" ", tmp);
			if (!v->var)
				return (NULL);
		}
		v3->new_line = 0;
	}
	if (ft_strlen(tmp) - 1 >= 0 && tmp[ft_strlen(tmp) - 1] == ' ')
		v3->new_line = 1;
	free(tmp);
	return ((void *)1337);
}
