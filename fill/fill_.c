/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:10:18 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:52 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_redr_type(t_strt **node, char *str)
{
	(*node)->redirect = ft_realloc_2d((*node)->redirect, str);
	if (!(*node)->command)
		(*node)->type = REDIR;
	(*node)->pr_exec = ft_realloc_arr(*node, REDIR);
	if (!(*node)->redirect || !(*node)->pr_exec)
		return (0);
	return (1337);
}

void	*fill_with_no_delem_2(t_strt *node, char **str, int i, t_mini *shell)
{
	void	*p_tmp;

	p_tmp = (void *)1337;
	if (ft_check_delm(str[i - 1], node->delem_1) == -1)
	{
		if (check_empty(shell, node, str, i) == 1)
			return ((void *)1337);
		if (!node->command)
			p_tmp = fill_cmd_type(&node, str[i], shell, -1);
		else
			p_tmp = fill_opt(&node, str[i], shell, -1);
	}
	else if (ft_check_delm(str[i - 1], node->delem_1) >= 0)
	{
		if (ft_strcmp_delm(">>", str[i - 1]) == 2)
			p_tmp = fill_ou_file(&node, str[i], shell, NULL);
		else
		{
			node->delemiter = ft_realloc_2d(node->delemiter, str[i]);
			if (!node->delemiter)
				return (NULL);
		}
	}
	return (p_tmp);
}

void	*fill_with_no_delem(t_strt *node, char **str, int i, t_mini *shell)
{
	if (i == 0)
	{
		if (check_empty(shell, node, str, i) == 1)
			return ((void *)1337);
		if (!fill_cmd_type(&node, str[i], shell, -1))
			return (NULL);
	}
	else if (ft_strcmp_delm("<", *(str + i - 1)) == 1)
	{
		if (!fill_in_file(&node, str[i], shell, NULL))
			return (NULL);
	}
	else if (ft_strcmp_delm(">", *(str + i - 1)) == 1)
	{
		if (!fill_ou_file(&node, str[i], shell, NULL))
			return (NULL);
	}
	else if (!fill_with_no_delem_2(node, str, i, shell))
		return (NULL);
	return ((void *)1337);
}

int	fill_compare(t_mini *shell, t_strt *node, char **dels, char **str)
{
	int		i_str;
	int		idx;

	i_str = -1;
	while (str[++i_str])
	{
		idx = ft_check_delm(str[i_str], dels);
		if ((str[i_str][0] == '>' || str[i_str][0] == '<') && !str[i_str][1])
		{
			if (!fill_redr_type(&node, str[i_str]))
				return (free_echoue(str, len_2d(str)), 0);
		}
		else if (idx >= 0)
		{
			if (!ft_type_special(node, *(str + i_str), idx))
				return (free_echoue(str, len_2d(str)), 0);
		}
		else if (idx == -1)
			if (!fill_with_no_delem(node, str, i_str, shell))
				return (free_echoue(str, len_2d(str)), 0);
	}
	return (1337);
}

int	fill_phase(t_mini *shell)
{
	t_strt	*stack;
	char	**str;

	stack = shell->stack;
	if (!fill_space(stack))
		return (0);
	while (stack)
	{
		str = ft_split(stack->str, ' ');
		if (!str)
			return (0);
		if (!fill_compare(shell, stack, stack->delem_1, str))
			return (0);
		ft_decal_value(stack->pr_exec, stack->pr_exec_size, CMD);
		free_echoue(str, len_2d(str));
		stack = stack->next;
	}
	return (1337);
}
