/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:56:38 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:11 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *str_1, char *str_2)
{
	int	i_dice_1;

	if (!str_1 || !str_2)
		return (0);
	i_dice_1 = -1;
	if (ft_strlen(str_1) != ft_strlen(str_2))
		return (0);
	while (str_1[++i_dice_1])
		if (str_1[i_dice_1] != str_2[i_dice_1])
			return (0);
	return (1);
}

int	ft_strcmp_value(char *str_1, char *str_2)
{
	int	i_dice;

	i_dice = 0;
	while (str_1[i_dice] && str_2[i_dice])
	{
		if (str_1[i_dice] != str_2[i_dice])
			return (str_1[i_dice] - str_2[i_dice]);
		i_dice++;
	}
	if (str_1[i_dice] != str_2[i_dice])
		return (str_1[i_dice] - str_2[i_dice]);
	return (0);
}

int	check_varname(char *str)
{
	if (!ft_strlen(str) || (!(str[0] >= 97 && str[0] <= 122)
			&& !(str[0] >= 65 && str[0] <= 90) && str[0] != '_'))
		return (0);
	while (*str && *str != '=')
	{
		if ((*str >= 65 && *str <= 90)
			|| (*str >= 97 && *str <= 122)
			|| (*str >= 48 && *str <= 57)
			|| *str == '_' || (*str == '+' && *(str + 1) == '='))
			str++;
		else
			return (0);
	}
	return (1);
}

void	*env_handle___soon(t_strt *node, t_env *env, void *p_tmp)
{
	char	*cmd;

	cmd = ft_strdup(node->command);
	if (!cmd)
		return (NULL);
	cmd = ft_rm_quotes(cmd, node, 0);
	if (!cmd)
		return (NULL);
	p_tmp = env_value_modifie(env, ft_strjoin("_=", cmd));
	return (free(cmd), p_tmp);
}
