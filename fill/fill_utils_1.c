/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:23:19 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:56 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_realloc_2d(char **o__pt, char *new_opt)
{
	int		i_dice;
	char	**p__tr;

	i_dice = 0;
	while (o__pt && o__pt[i_dice])
		i_dice++;
	p__tr = malloc((i_dice + 2) * sizeof(char *));
	while (!p__tr)
		return (free_echoue(o__pt, len_2d(o__pt)), perror("minishell"), NULL);
	(1337) && (p__tr[i_dice + 1] = NULL, i_dice = 0);
	while (o__pt && o__pt[i_dice])
	{
		p__tr[i_dice] = malloc(ft_strlen(o__pt[i_dice]) + 1);
		if (!p__tr[i_dice])
			return (free_echoue(p__tr, i_dice),
				free_echoue(o__pt, len_2d(o__pt)), perror("minishell"), NULL);
		ft_strncpy(p__tr[i_dice], o__pt[i_dice], ft_strlen(o__pt[i_dice]));
		i_dice++;
	}
	p__tr[i_dice] = malloc(ft_strlen(new_opt) + 1);
	if (!p__tr[i_dice])
		return (free_echoue(p__tr, i_dice),
			free_echoue(o__pt, len_2d(o__pt)), perror("minishell"), NULL);
	ft_strncpy(p__tr[i_dice], new_opt, ft_strlen(new_opt));
	return (free_echoue(o__pt, i_dice), p__tr);
}

char	*ft_realloc_with_space(char *str, int i_dice_space)
{
	char	*new_str;
	int		i_dice;
	int		i_dice_new;

	new_str = malloc(ft_strlen(str) + 2);
	if (!new_str)
		return (free(str), perror("minishell"), NULL);
	new_str[ft_strlen(str) + 1] = '\0';
	i_dice = 0;
	i_dice_new = 0;
	while (str[i_dice])
	{
		new_str[i_dice_new] = str[i_dice];
		(i_dice == i_dice_space) && (new_str[++i_dice_new] = ' ');
		i_dice_new++;
		i_dice++;
	}
	free(str);
	return (new_str);
}

int	*ft_realloc_arr(t_strt *stack, int type)
{
	int	*arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(int) * (stack->pr_exec_size + 1));
	if (!arr)
		return (free(stack->pr_exec), perror("minishell"), NULL);
	while (stack->pr_exec_size && i < stack->pr_exec_size)
	{
		arr[i] = stack->pr_exec[i];
		i++;
	}
	arr[i] = type;
	free(stack->pr_exec);
	stack->pr_exec_size++;
	return (arr);
}

int	*ft_ralloc_ofile_flag(t_strt *stack, int type)
{
	int	*arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(int) * (stack->ofile_flag_size + 1));
	if (!arr)
		return (free(stack->ofile_flag), perror("minishell"), NULL);
	while (stack->ofile_flag_size && i < stack->ofile_flag_size)
	{
		arr[i] = stack->ofile_flag[i];
		i++;
	}
	arr[i] = type;
	free(stack->ofile_flag);
	stack->ofile_flag_size++;
	return (arr);
}

int	*ft_ralloc_ifile_flag(t_strt *stack, int type)
{
	int	*arr;
	int	i;

	i = 0;
	arr = malloc(sizeof(int) * (stack->ifile_flag_size + 1));
	if (!arr)
		return (free(stack->ifile_flag), perror("minishell"), NULL);
	while (stack->ifile_flag_size && i < stack->ifile_flag_size)
	{
		arr[i] = stack->ifile_flag[i];
		i++;
	}
	arr[i] = type;
	free(stack->ifile_flag);
	stack->ifile_flag_size++;
	return (arr);
}
