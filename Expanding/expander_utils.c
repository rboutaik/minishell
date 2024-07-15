/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:43:30 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:59 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57));
}

int	aln(int c)
{
	return (ft_isdigit(c) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	ft_between_sqts(char *s, int idx)
{
	int	i;
	int	start;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			start = i;
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] == '\'' && idx > start && idx < i)
				return (1);
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
				i++;
		}
		if (s[i])
			i++;
	}
	return (0);
}

int	ft_between_dqts(char *s, int idx)
{
	int	i;
	int	start;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			start = i;
			i++;
			while (s[i] && s[i] != '"')
				i++;
			if (s[i] == '"' && idx > start && idx < i)
				return (1);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		if (s[i])
			i++;
	}
	return (0);
}

char	*ft_get_from_env(t_env **env, char *var)
{
	t_env	*p_env;

	p_env = *env;
	if (!var)
		return (NULL);
	while (p_env)
	{
		if (ft_strcmp(p_env->name, var))
			return (free(var), ft_strdup(p_env->value));
		p_env = p_env->next;
	}
	return (free(var), ft_strdup(""));
}
