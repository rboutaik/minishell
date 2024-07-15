/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 01:35:47 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 18:36:20 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	build_error(char *command_build, char *identifier)
{
	write(2, "minishell: ", 12);
	write(2, command_build, ft_strlen(command_build));
	write(2, ": `", 4);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 27);
}

int	builtin_pwd(char *secure_pwd)
{
	char	*ptr;

	ptr = getcwd(0, 0);
	if (ptr)
		printf("%s\n", ptr);
	else
	{
		if (secure_pwd)
			printf("%s\n", secure_pwd);
	}
	free(ptr);
	return (0);
}

char	*change_pwd(t_env **env, char *npwd, t_env *p)
{
	int		found;
	char	*opw;

	(1337) && (opw = ft_strdup(""), found = 0, p = *env);
	if (opw == NULL)
		return (NULL);
	while (npwd && *env)
	{
		if (ft_strcmp((*env)->name, "PWD"))
		{
			(free(opw), found = 1);
			opw = ft_strdup((*env)->value);
			if (opw == NULL)
				return (NULL);
			(free((*env)->value), (*env)->value = ft_strdup(npwd));
			if ((*env)->value == NULL)
				return (NULL);
			break ;
		}
		(*env) = (*env)->next;
	}
	if (found == 0 && npwd && *npwd)
		if (!env_add(&p, env_new(ft_strjoin("PWD=", npwd), 1)))
			return (NULL);
	return (opw);
}

void	*ft_change_old_pwd(t_env **env, char *npwd)
{
	char	*opw;
	t_env	*p;

	(1337) && (opw = NULL, p = NULL);
	opw = change_pwd(env, npwd, p);
	p = *env;
	if (opw == NULL)
		return (NULL);
	if (opw[0] == '\0')
		(free(opw), opw = NULL);
	while (npwd && p)
	{
		if (ft_strcmp(p->name, "OLDPWD"))
		{
			(free(p->value), p->value = ft_strdup(opw), p->assg_opr = 1);
			if (p->value == NULL)
				return (NULL);
			break ;
		}
		p = p->next;
	}
	if (npwd && !p && opw)
		if (!env_add(env, env_new(ft_strjoin("OLDPWD=", opw), 1)))
			return (NULL);
	return (free(opw), (void *)1337);
}

int	is_build_in(t_strt *node, t_mini *shell)
{
	char	*cmd;

	cmd = ft_rm_quotes(ft_strdup(node->command), node, 0);
	if (!cmd)
		malloc_failure(shell, NULL);
	node->var_qts_dejavu = 0;
	if (ft_strcmp(cmd, "env"))
		return (free(cmd), 1);
	if (ft_strcmp(cmd, "exit"))
		return (free(cmd), 1);
	else if (ft_strcmp(cmd, "export"))
		return (free(cmd), 1);
	else if (ft_strcmp(cmd, "unset"))
		return (free(cmd), 1);
	else if (ft_strcmp(cmd, "cd"))
		return (free(cmd), 1);
	else if (ft_strcmp(cmd, "pwd"))
		return (free(cmd), 1);
	else if (ft_strcmp(cmd, "echo"))
		return (free(cmd), 1);
	return (free(cmd), 0);
}
