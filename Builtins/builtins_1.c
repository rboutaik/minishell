/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:30:19 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:15 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isoption(char *str)
{
	int	str_dice;

	str_dice = 0;
	if (!str[str_dice])
		return (0);
	if (str[str_dice] == '-' && str[str_dice + 1] == 'n')
	{
		str_dice += 2;
		while (str[str_dice] && str[str_dice] == 'n')
			str_dice++;
	}
	if (!str[str_dice])
		return (1);
	return (0);
}

int	ft_calc_quotes(char *str, t_strt *p_tr)
{
	int		quote_count;
	int		str_dice;
	char	quote;
	int		size;

	(1337) && (str_dice = 0, quote_count = 0, size = ft_strlen(str));
	while (str_dice < size)
	{
		if ((str[str_dice] == '"' || str[str_dice] == '\'')
			&& (!p_tr
				|| !ft_in_arr(str_dice, p_tr,
					p_tr->var_qts, p_tr->var_qts_size)))
		{
			(1337) && (quote = str[str_dice], str_dice++);
			while (str[str_dice] && (str[str_dice] != quote
					|| ft_in_arr(str_dice, p_tr,
						p_tr->var_qts, p_tr->var_qts_size)))
				str_dice++;
			if (str[str_dice] == quote && !ft_in_arr(str_dice, p_tr,
					p_tr->var_qts, p_tr->var_qts_size))
				quote_count += 2;
		}
		str_dice++;
	}
	return (quote_count);
}

char	*ft_rm_quotes(char *s, t_strt *p_tr, int flag)
{
	char	*str;
	int		i;
	int		j;
	char	q;

	(1337) && (j = 0, i = -1);
	str = malloc(sizeof(char) * (ft_strlen(s) - (ft_calc_quotes(s, p_tr)) + 1));
	if (!str)
		return (free(s), perror("minishell"), NULL);
	while (++i < ft_strlen(s))
	{
		if ((s[i] == '"' || s[i] == '\'') && (!p_tr
				|| !ft_in_arr(i, p_tr, p_tr->var_qts, p_tr->var_qts_size)))
		{
			q = s[i++];
			while (s[i] && (s[i] != q || (s[i] == q && p_tr && ft_in_arr(i,
							p_tr, p_tr->var_qts, p_tr->var_qts_size))))
				str[j++] = s[i++];
		}
		else
			str[j++] = s[i];
	}
	(p_tr != NULL && flag) && (free(p_tr->var_qts), p_tr->var_qts = NULL);
	return ((flag) && (p_tr->var_qts_size = 0), str[j] = '\0', free(s),
		(flag) && (p_tr->var_qts_dejavu = 1), str);
}

int	builtin_echo(t_strt *stack)
{
	int	option;
	int	i;

	i = 0;
	option = 0;
	while (stack->option && stack->option[i] && ft_isoption(stack->option[i]))
	{
		option = 1;
		i++;
	}
	while (stack->option && stack->option[i])
	{
		ft_putstr_fd(stack->option[i], 1);
		if (stack->option[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		printf("\n");
	return (0);
}

int	build_env(t_env **env, t_mini *shell)
{
	t_env	*p_env;

	p_env = *env;
	if (env_value_modifie(p_env, ft_strdup("_=/usr/bin/env")) == NULL)
		malloc_failure(shell, NULL);
	while (p_env)
	{
		if (p_env->assg_opr != 2 && p_env->value)
		{
			write (1, p_env->name, ft_strlen(p_env->name));
			write (1, "=", 1);
			write (1, p_env->value, ft_strlen(p_env->value));
			write (1, "\n", 1);
		}
		p_env = p_env->next;
	}
	return (0);
}
