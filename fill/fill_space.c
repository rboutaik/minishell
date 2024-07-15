/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:01:44 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:55 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fill_space_after(t_strt **stack)
{
	t_strt	*p_stack;
	int		i_str;

	i_str = 0;
	p_stack = *stack;
	while (p_stack->str[i_str])
	{
		if (i_str && (p_stack->str[i_str] == '<' || p_stack->str[i_str] == '>')
			&& !(p_stack->str[i_str + 1] == '<'
				|| p_stack->str[i_str + 1] == '>'))
		{
			if (ft_check_qts(p_stack->str, i_str - 1) == 0)
			{
				p_stack->str = ft_realloc_with_space(p_stack->str, i_str++);
				if (!p_stack->str)
					return (0);
			}
		}
		i_str += (p_stack->str[i_str] != '\0');
	}
	return (1337);
}

int	fill_space_before_red_2(t_strt **stack, int *i_str)
{
	if (!*i_str && (*stack)->str[*i_str + 1] && ((*stack)->str[0] == '<'
			|| (*stack)->str[0] == '>') && ((*stack)->str[*i_str + 1] != '<'
			&& (*stack)->str[*i_str + 1] != '>'))
	{
		if (ft_check_qts((*stack)->str, *i_str) == 0)
		{
			(*stack)->str = ft_realloc_with_space((*stack)->str, (*i_str)++);
			if (!(*stack)->str)
				return (0);
		}
	}
	return (1337);
}

int	fill_space_before_red_1(t_strt **stack, int *i_str)
{
	if (*i_str && (*stack)->str[*i_str]
		&& ((*stack)->str[*i_str] == '<'
			|| (*stack)->str[*i_str] == '>')
		&& !((*stack)->str[*i_str - 1] == '<'
			|| (*stack)->str[*i_str - 1] == '>'))
	{
		if (ft_check_qts((*stack)->str, *i_str) == 0)
		{
			(*stack)->str = ft_realloc_with_space((*stack)->str,
					(*i_str)++ - 1);
			if (!(*stack)->str)
				return (0);
		}
	}
	return (1337);
}

int	fill_space_before(t_strt **stack)
{
	t_strt	*p_stack;
	int		i_str;

	i_str = 0;
	p_stack = *stack;
	while (p_stack->str[i_str])
	{
		if (!fill_space_before_red_1(&p_stack, &i_str)
			|| !fill_space_before_red_2(&p_stack, &i_str))
			return (0);
		i_str++;
	}
	return (1337);
}

int	fill_space(t_strt *stack)
{
	t_strt	*p_stack;

	p_stack = stack;
	while (p_stack)
	{
		if (!fill_space_before(&p_stack)
			|| !fill_space_after(&p_stack))
			return (0);
		p_stack = p_stack->next;
	}
	return (1337);
}
