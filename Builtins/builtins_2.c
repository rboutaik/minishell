/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:09:14 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:16 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_unset(t_env **env, char **p__splt)
{
	int	exit_status;
	int	i;

	i = -1;
	exit_status = 0;
	while (p__splt && p__splt[++i])
	{
		if (!ft_strcmp(p__splt[i], "_"))
		{
			if (check_varname(p__splt[i]) && !ft_char_check(p__splt[i], '='))
				unset_var(env, p__splt[i]);
			else
			{
				write(2, "minishell: unset: `", 20);
				write(2, p__splt[i], ft_strlen(p__splt[i]));
				write(2, "': not a valid identifier\n", 27);
				exit_status = 1;
			}
		}
	}
	return (exit_status);
}

void	export_caller(t_mini *shell, char **p__splt, int i, int *exit_status)
{
	t_env	**env;
	int		tmp;

	env = &shell->env;
	if (check_varname(p__splt[i]))
	{
		tmp = env_name_check(*env, p__splt[i]);
		if (tmp == 1 && ft_char_check(p__splt[i], '='))
		{
			if (env_value_modifie(*env, ft_strdup(p__splt[i])) == NULL)
				malloc_failure(shell, NULL);
		}
		else
		{
			tmp = env_name_check(*env, p__splt[i]);
			if (!tmp)
				env_add_front(env, env_new(ft_strdup(p__splt[i]),
						(ft_char_check(p__splt[i], '=') != NULL)), shell);
		}
		if (tmp == -1)
			malloc_failure(shell, NULL);
	}
	else
		(build_error("export", p__splt[i]), *exit_status = 1);
}

int	build_export(t_env **env, char **p__splt, t_mini *shell)
{
	int		i;
	int		exit_status;

	(1337) && (i = -1, exit_status = 0);
	if (len_2d(p__splt) == 0)
	{
		if (ft_sort_env(*env) == NULL)
			malloc_failure(shell, NULL);
	}
	else
	{
		while (p__splt[++i])
			export_caller(shell, p__splt, i, &exit_status);
	}
	return (exit_status);
}

void	*ft_value_changer(t_env *env, char *str, int i_dice, int flag)
{
	char	*tmp_str;

	tmp_str = NULL;
	if (flag && env)
	{
		tmp_str = ft_strjoin(env->value, str + i_dice + 2);
		if (!tmp_str)
			return (NULL);
		(free(env->value), env->value = tmp_str);
	}
	else
	{
		if (env)
		{
			free(env->value);
			env->value = malloc((ft_strlen(str) - i_dice) + 1);
			if (!env->value)
				return (perror("minishell"), NULL);
			ft_strncpy(env->value, str + i_dice + 1, ft_strlen(str) - i_dice);
		}
		else
			if (!env_add(&env, env_new(ft_strdup(str), 1)))
				return (NULL);
	}
	return ((void *)1337);
}
