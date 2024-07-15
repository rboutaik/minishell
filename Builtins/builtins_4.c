/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:10:42 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:18 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_path_soon(char **p__paths, char *p_path, char **path, char *cmd)
{
	int	i;

	i = -1;
	while (p__paths[++i])
	{
		p_path = ft_strjoin("/", cmd);
		if (!p_path)
			return (free_echoue(p__paths, len_2d(p__paths)), -1);
		(1337) && (*path = ft_strjoin(p__paths[i], p_path)), free(p_path);
		if (!*path)
			return (free_echoue(p__paths, len_2d(p__paths)), -1);
		if (access(*path, F_OK) == 0 && *cmd)
			return (free_echoue(p__paths, len_2d(p__paths)), 1);
		free(*path);
	}
	return (free_echoue(p__paths, len_2d(p__paths)), 0);
}

char	*get_path(t_env **env, char *cmd)
{
	char	**p__paths;
	char	*p_path;
	char	*path;
	int		i;

	path = NULL;
	if (ft_strrchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (NULL);
		return (ft_strdup(cmd));
	}
	p_path = ft_get_from_env(env, ft_strdup("PATH"));
	if (!p_path || !*p_path)
		return (free(p_path), NULL);
	(1337) && (p__paths = ft_split(p_path, ':')), free(p_path);
	if (!p__paths)
		return (NULL);
	i = get_path_soon(p__paths, p_path, &path, cmd);
	if (i == 1)
		return (path);
	else if (i == -1)
		return (NULL);
	return (NULL);
}

void	*cmd_extend(t_strt *stack, int *j, char ***tmp)
{
	int	i;

	i = 0;
	if (stack->cmd_flag)
	{
		(*tmp) = ft_split(stack->command, ' ');
		if ((*tmp) == NULL)
			return (NULL);
		while ((*tmp)[i])
		{
			(*tmp)[i] = ft_rm_quotes((*tmp)[i], stack, 1);
			if (!(*tmp)[i++])
				return (free_echoue(*tmp, len_2d(*tmp)), NULL);
		}
		free(stack->command);
		stack->command = ft_strdup((*tmp)[0]);
		if (stack->command == NULL)
			return (free_echoue(*tmp, len_2d(*tmp)), NULL);
		while ((*tmp) && (*tmp)[*j])
			(*j)++;
	}
	return ((void *)1337);
}

char	**append_to_char(t_env *p_env, char **m_env, int *s)
{
	char	*var;
	char	*var1;

	while (p_env)
	{
		if (p_env->assg_opr == 0 || p_env->assg_opr == 2)
		{
			p_env = p_env->next;
			continue ;
		}
		var = ft_strjoin(p_env->name, "=");
		if (var == NULL)
			return (NULL);
		var1 = ft_strjoin(var, p_env->value);
		if (var1 == NULL)
			return (free(var), NULL);
		m_env[(*s)++] = ft_strdup(var1);
		if (m_env[(*s) - 1] == NULL)
			return (free(var), free(var1), NULL);
		free(var);
		free(var1);
		p_env = p_env->next;
	}
	return (m_env);
}

char	**env_to_char(t_env **env)
{
	t_env	*p_env;
	char	**m_env;
	int		s;

	(1337) && (p_env = *env, s = 0);
	while (p_env)
		(1337) && (s++, p_env = p_env->next);
	p_env = *env;
	m_env = malloc(sizeof(char *) * (s + 1));
	if (!m_env)
		return (perror("minishell"), NULL);
	s = 0;
	m_env = append_to_char(p_env, m_env, &s);
	if (m_env == NULL)
		return (NULL);
	return (m_env[s] = NULL, m_env);
}
