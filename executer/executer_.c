/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:54:42 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:10 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_sort_env(t_env *env)
{
	int		flag_checker;
	int		i__dice;
	char	**p__tr;
	t_env	*p_env;

	i__dice = -1;
	flag_checker = 1;
	p__tr = malloc(sizeof(char *) * (ft_stack_len(env) + 1));
	if (!p__tr)
		return (perror("minishell"), NULL);
	p_env = env;
	while (++i__dice < ft_stack_len(env))
	{
		p__tr[i__dice] = ft_strdup(p_env->name);
		if (p__tr[i__dice] == NULL)
			return (free_echoue(p__tr, i__dice), NULL);
		p_env = p_env->next;
	}
	p__tr[i__dice] = NULL;
	ft_sort_2d(p__tr);
	exct_affch_export(env, p__tr);
	return (free_echoue(p__tr, len_2d(p__tr)), (void *)1337);
}

int	len_2d(char **array)
{
	int	i_dice;

	i_dice = 0;
	while (array && array[i_dice])
		i_dice++;
	return (i_dice);
}

void	unset_var_1(t_env ***env, t_env **p_env, t_env	**tmp_env, int i_dice)
{
	if (!i_dice)
	{
		**env = (**env)->next;
		free((*tmp_env)->name);
		free((*tmp_env)->value);
		free(*tmp_env);
		*p_env = **env;
	}
	else
	{
		(*tmp_env)->next = (*p_env)->next;
		free((*p_env)->name);
		free((*p_env)->value);
		free((*p_env));
		(*p_env) = *tmp_env;
	}
}

void	unset_var(t_env **env, char *var)
{
	t_env	*tmp_env;
	t_env	*p_env;
	int		i_dice;

	i_dice = 0;
	p_env = *env;
	tmp_env = *env;
	while (p_env)
	{
		if (ft_strcmp(p_env->name, var))
			unset_var_1(&env, &p_env, &tmp_env, i_dice);
		i_dice++;
		tmp_env = p_env;
		if (p_env)
			p_env = p_env->next;
	}
}

int	executer_phase(t_mini *shell, t_strt *node, int in_child)
{
	int		exit_status;

	exit_status = builtin_execve(shell, node, in_child);
	return (exit_status);
}
