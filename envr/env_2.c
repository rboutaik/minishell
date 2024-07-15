/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:27:09 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:13 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*p;
	int		size;

	size = ft_strlen(s1);
	p = malloc(size + 1);
	if (!p)
		return (perror("minishell"), NULL);
	ft_strncpy(p, s1, size);
	p[size] = '\0';
	return (p);
}

char	*ft_strndup(char *s1, int size)
{
	char	*p;

	p = malloc(size + 1);
	if (!p)
		return (perror("minishell"), NULL);
	ft_strncpy(p, s1, size);
	p[size] = '\0';
	return (p);
}

int	env_find(t_env *env, char *name)
{
	t_env	*p_env;

	p_env = env;
	while (p_env)
	{
		if (ft_strcmp(p_env->name, name))
			return (1);
		p_env = p_env->next;
	}
	return (0);
}

t_env	*env_new(char *content, int assg_opr)
{
	int		size;
	t_env	*t;

	size = 0;
	if (!content)
		return (NULL);
	t = malloc(sizeof(t_env));
	if (!t)
		return (free(content), perror("minishell"), NULL);
	t->assg_opr = assg_opr;
	while (content[size] && content[size] != '=')
		size++;
	t->name = ft_strndup(content, size - (content[size - 1] == '+'));
	if (!t->name)
		return (free(content), free(t), NULL);
	size -= !content[size];
	(content[size] != '=') && (t->value = NULL);
	if (content[size] == '=')
	{
		t->value = ft_strdup(content + size + 1);
		if (!t->value)
			return (free(content), free(t->name), free(t), NULL);
	}
	return (free(content), t->next = NULL, t);
}

void	env_add_front(t_env **lst, t_env *new, t_mini *shell)
{
	if (new == NULL)
		malloc_failure(shell, NULL);
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
