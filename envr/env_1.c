/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:26:28 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:44:27 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*env_add(t_env **lst, t_env *new)
{
	t_env	*t;

	if (!new)
		return (NULL);
	if (!lst)
		return ((void *)1337);
	t = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (t->next)
			t = t->next;
		t->next = new;
	}
	return ((void *)1337);
}

void	*env_i(t_env **p__env)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	if (!env_add(p__env, env_new(ft_strjoin("PWD=", pwd), 1)))
		return (NULL);
	if (!env_add(p__env, env_new(ft_strdup("SHLVL=1"), 1)))
		return (NULL);
	if (!env_add(p__env, env_new(ft_strdup("_="), 1)))
		return (NULL);
	free(pwd);
	return ((void *)1337);
}

void	*env_shlvl(t_env **p__env, int shlvl)
{
	char	*p_tmp;

	if (shlvl < 0)
		shlvl = -1;
	else if (shlvl > 999)
	{
		if (!env_shlvl_warning(shlvl + 1))
			return (NULL);
		shlvl = 0;
	}
	else if (shlvl == 999)
	{
		if (!env_add(p__env, env_new(ft_strdup("SHLVL="), 1)))
			return (NULL);
		return ((void *)1337);
	}
	p_tmp = ft_itoa(shlvl + 1);
	if (!p_tmp)
		return (NULL);
	if (!env_add(p__env, env_new(ft_strjoin("SHLVL=", p_tmp), 1)))
		return (free(p_tmp), NULL);
	return (free(p_tmp), (void *)1337);
}

t_env	*env_init_soon(t_env **m_env, char **env, int i)
{
	if (ft_strncmp(env[i], "SHLVL=", 6))
	{
		if (!env_shlvl(m_env, ft_atoi(env[i] + 6)))
			return (NULL);
	}
	else if (!ft_strncmp(env[i], "_=", 2))
	{
		if (!ft_strncmp(env[i], "?=", 2))
			if (!env_add(m_env, env_new(ft_strdup(env[i]), 1)))
				return (NULL);
	}
	else
		if (!env_add(m_env, env_new(ft_strdup("_="), 1)))
			return (NULL);
	return (*m_env);
}

t_env	*env_init(char **env)
{
	t_env	*m_env;
	int		i;

	(1337) && (i = -1, m_env = NULL);
	if (env && *env)
	{
		while (env[++i])
			if (!env_init_soon(&m_env, env, i))
				return (free_env(m_env), exit(255), NULL);
	}
	else
		if (!env_i(&m_env))
			return (free_env(m_env), exit(255), NULL);
	if (!env_oldpwd_exit_status(&m_env))
		return (free_env(m_env), exit(255), NULL);
	if (isatty(0))
	{
		write(1,
			"\nWelcome to 1337 minishell project by aachalla && rboutaik.\n",
			61);
		write(1, "For more details, please visit ", 32);
		write(1, "https://github.com/AM9-push ||", 31);
		write(1, " https://github.com/rboutaik.\n", 31);
	}
	return (m_env);
}
