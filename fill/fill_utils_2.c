/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:25:15 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:57 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_qts(char *str, int i_dice)
{
	int	d_quote[2];
	int	s_quote[2];
	int	i;

	i = i_dice;
	d_quote[0] = 0;
	d_quote[1] = 0;
	s_quote[0] = 0;
	s_quote[1] = 0;
	if (i >= ft_strlen(str))
		return (0);
	while (i >= 0)
	{
		(str[i] == '"') && (d_quote[0]++);
		(str[i--] == '\'') && (s_quote[0]++);
	}
	i = i_dice;
	while (str[i])
	{
		(str[i] == '"') && (d_quote[1]++);
		(str[i++] == '\'') && (s_quote[1]++);
	}
	return (((d_quote[0] % 2) && (d_quote[1]))
		|| ((s_quote[0] % 2) && (s_quote[1])));
}

int	ft_check_delm(char *cmd, char *d_lemiter[])
{
	int	i_dice;
	int	tmp_cmp;

	i_dice = -1;
	while (++i_dice < 7)
	{
		tmp_cmp = ft_strcmp_delm(cmd, d_lemiter[i_dice]);
		if (tmp_cmp >= 0)
			return (i_dice);
	}
	return (-1);
}

void	*ft_type_special_2(t_strt *stack, char *str, int del_dice)
{
	if (del_dice == 2)
	{
		stack->here_doc = ft_realloc_2d(stack->here_doc, str);
		if (!stack->command)
			stack->type = HERE_DOC;
		stack->pr_exec = ft_realloc_arr(stack, HERE_DOC);
		if (!stack->here_doc && !stack->pr_exec)
			return (NULL);
	}
	else if (del_dice == 3)
	{
		stack->append = ft_realloc_2d(stack->append, str);
		if (!stack->command)
			stack->type = APPEND;
		stack->pr_exec = ft_realloc_arr(stack, APPEND);
		if (!stack->append || !stack->pr_exec)
			return (NULL);
	}
	return ((void *)1337);
}

void	*ft_type_special(t_strt *stack, char *str, int del_dice)
{
	if (del_dice == 0 || del_dice == 1)
		stack->type = ACCOL;
	else if (del_dice == 2 || del_dice == 3)
	{
		if (!ft_type_special_2(stack, str, del_dice))
			return (NULL);
		return ((void *)1337);
	}
	else if (del_dice == 4)
		stack->type = OR;
	else if (del_dice == 5)
		stack->type = PIPE;
	else if (del_dice == 6)
		stack->type = AND;
	stack->pr_exec = ft_realloc_arr(stack, stack->type);
	if (!stack->pr_exec)
		return (NULL);
	return ((void *)1337);
}

void	ft_decal_value(int *array, int size, int value)
{
	int	i_dice;
	int	tmp_val;

	i_dice = -1;
	while (++i_dice < size)
	{
		if (array[i_dice] == value)
		{
			while (i_dice)
			{
				tmp_val = array[i_dice];
				array[i_dice] = array[i_dice - 1];
				array[i_dice - 1] = tmp_val;
				i_dice--;
			}
			return ;
		}
	}
}
