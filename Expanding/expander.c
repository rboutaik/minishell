/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 00:40:10 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:01 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*ft_alloc_int_arr(t_strt *stack, int type)
{
	int	*arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(int) * (stack->var_qts_size + 1));
	if (!arr)
		return (free(stack->var_qts), perror("minishell"), NULL);
	while (stack->var_qts_size && i < stack->var_qts_size)
	{
		arr[i] = stack->var_qts[i];
		i++;
	}
	arr[i] = type;
	free(stack->var_qts);
	stack->var_qts_size++;
	return (arr);
}

int	can_i_expand(char *p, int i)
{
	if (((!aln(p[i]) && p[i] != '_') || ft_between_sqts(p, i - 1))
		&& ((p[i] != '\'' && p[i] != '"') || ft_between_dqts(p, i - 1)
			|| ft_between_sqts(p, i - 1)))
		if (!(p[i] == '?'))
			return (1);
	return (0);
}

char	*ft_expand_it(char *s, t_vars3 *v3, t_strt *p_tr, int *var_size)
{
	t_vars2	v;

	if (!vars_init_2(&v, v3, s))
		return (free(s), NULL);
	(exp_echo_flag(p_tr, &v, v3, s), *var_size = check_ambig(s, &v, v3, p_tr));
	if (check_for_space(&v, v3, s) == NULL)
		return (free_echoue(v.tmp, len_2d(v.tmp)), free(v.var), NULL);
	if (*var_size == 1)
		return (free_echoue(v.tmp, len_2d(v.tmp)), free(v.var),
			free(s), ft_strdup(v3->str));
	if (*var_size == -1)
		return (free_echoue(v.tmp, len_2d(v.tmp)), free(v.var), NULL);
	if (!calc_words(s, &v))
		return (free(s), free_echoue(v.tmp, len_2d(v.tmp)), free(v.var), NULL);
	while (s[v.i])
	{
		if (!bind_vars(p_tr, &v, v3))
			return (free(s), free_echoue(v.tmp, len_2d(v.tmp)),
				free(v.str), free(v.var), NULL);
		if (!s[v.i])
			break ;
		v.str[v.j++] = s[v.i++];
	}
	return (v.str[v.j] = '\0', *var_size = ft_calc(v.j - ft_strlen(s)),
		free(v.var), free_echoue(v.tmp, len_2d(v.tmp)), free(s), v.str);
}

char	*ft_expander(char *s, t_env **env, t_strt *p_tr, char *expanded_var)
{
	t_vars3	v3;
	char	*p;
	int		i;

	vars_init_3(&v3, env, expanded_var, s);
	if (!s)
		return (NULL);
	(1337) && (i = -1), p = ft_strdup(s);
	if (!p)
		return (free(s), NULL);
	while (p && i < ft_strlen(p) && p[++i])
	{
		if (p[i] == '$')
		{
			if (can_i_expand(p, ++i))
				continue ;
			var_end(p, &v3, &i);
			p = ft_expand_it(p, &v3, p_tr, &v3.var_size);
			if (!p || ft_strcmp(s, p))
				return (free(s), p);
			i = v3.start + v3.var_size - 2;
		}
	}
	return (free(s), p);
}

void	sec_close(t_mini *shell, int sec_in_out[])
{
	if (dup2(sec_in_out[1], STDOUT_FILENO) == -1)
	{
		perror("minishell");
		malloc_failure(shell, NULL);
	}
	if (dup2(sec_in_out[0], STDIN_FILENO) == -1)
	{
		close(sec_in_out[1]);
		perror("minishell");
		malloc_failure(shell, NULL);
	}
	close(sec_in_out[1]);
	close(sec_in_out[0]);
}
