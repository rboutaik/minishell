/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:55:52 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:10 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_char_check(char *str, char c)
{
	int	i_dice;

	i_dice = -1;
	while (str[++i_dice])
		if (str[i_dice] == c)
			return (str + i_dice);
	return (NULL);
}

int	env_name_check(t_env *env, char *name)
{
	int		i_dice;
	int		size;
	char	*tmp_name;

	i_dice = -1;
	size = 0;
	while (name[++i_dice] && name[i_dice] != '=' && name[i_dice] != '+')
		size++;
	tmp_name = malloc(size + 1);
	if (tmp_name == NULL)
		return (perror("minishell"), -1);
	tmp_name[size] = '\0';
	i_dice = -1;
	while (++i_dice < size && name[i_dice] != '=')
		tmp_name[i_dice] = name[i_dice];
	while (env)
	{
		if (ft_strcmp(env->name, tmp_name))
			return (free(tmp_name), 1);
		env = env->next;
	}
	return (free(tmp_name), 0);
}

void	ft_sort_2d(char **p__tr)
{
	int		flag_sort;
	int		i__dice;
	char	*p_tmp;

	flag_sort = 1;
	while (flag_sort)
	{
		flag_sort = 0;
		i__dice = -1;
		while (p__tr && p__tr[++i__dice] && p__tr[i__dice + 1])
		{
			if (ft_strcmp_value(p__tr[i__dice], p__tr[i__dice + 1]) > 0)
			{
				p_tmp = p__tr[i__dice];
				p__tr[i__dice] = p__tr[i__dice + 1];
				p__tr[i__dice + 1] = p_tmp;
				flag_sort = 1;
			}
		}
	}
}

int	ft_stack_len(t_env *p_env)
{
	int	count;

	count = 0;
	while (p_env)
	{
		count++;
		p_env = p_env->next;
	}
	return (count);
}

void	exct_affch_export(t_env *env, char **p__tr)
{
	int		i__dice;
	t_env	*p_env;

	p_env = env;
	i__dice = -1;
	while (p__tr[++i__dice])
	{
		p_env = env;
		while (p_env)
		{
			if (ft_strcmp(p_env->name, p__tr[i__dice])
				&& !ft_strcmp(p_env->name, "_") && !ft_strcmp(p_env->name, "?"))
			{
				printf("declare -x %s", p_env->name);
				if (p_env->value)
					printf("=\"%s\"", p_env->value);
				printf("\n");
			}
			p_env = p_env->next;
		}
	}
}
