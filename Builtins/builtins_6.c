/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:59:27 by aachalla          #+#    #+#             */
/*   Updated: 2024/05/23 16:11:55 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strdigit(char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!(*str >= 48 && *str <= 57))
			return (0);
		str++;
	}
	return (1);
}

int	at_ext(char *str)
{
	int		i_str;
	int		signe;
	long	n1;
	long	n2;

	n1 = 0;
	n2 = 0;
	i_str = 0;
	signe = 1;
	if (str[0] == '+' || str[0] == '-')
	{
		if (str[i_str++] == '-')
			signe = -1;
	}
	while (str[i_str])
	{
		n2 = n1;
		n1 = n1 * 10 + (str[i_str++] - '0');
		if ((n2 > n1 && signe == 1)
			|| (n1 < 0 && n2 > 0 && n1 != LONG_MIN))
			return (-2);
	}
	if (signe == -1)
		return ((unsigned char) -n1);
	return ((unsigned char) n1);
}

int	builtin_exit_soon(t_mini *shell, char **p__tr, char *s, int exit_cmd_f)
{
	int		exit_status;
	char	**p__tmp;
	int		arg_stat;

	p__tmp = ft_split(p__tr[0], ' ');
	if (!p__tmp)
		return (-1);
	arg_stat = ft_strdigit(*p__tmp);
	if (arg_stat == -1)
		return (free_echoue(p__tmp, len_2d(p__tmp)), -1);
	if (!arg_stat)
		return ((!exit_cmd_f) && (printf("exit\n")), ext_err(p__tr[0]),
			free_echoue(p__tmp, len_2d(p__tmp)), free_shell(shell), free(s),
			exit(255), 0);
	if (!p__tr[1])
	{
		if (at_ext(*p__tmp) == -2)
			return ((!exit_cmd_f) && (write(2, "exit\n", 6)), ext_err(p__tr[0]),
				free_echoue(p__tmp, len_2d(p__tmp)), free_shell(shell), free(s),
				exit(255), 0);
		return ((!exit_cmd_f) && (write(2, "exit\n", 6)),
			exit_status = at_ext(*p__tmp), free_shell(shell), free(s),
			free_echoue(p__tmp, len_2d(p__tmp)), exit(exit_status), 0);
	}
	return (free_echoue(p__tmp, len_2d(p__tmp)), 0);
}

int	builtin_exit(t_mini *shell, char **p__tr, int exit_cmd_f)
{
	int		exit_status;
	char	**p__tmp;
	char	*s;

	p__tmp = NULL;
	(p__tr != NULL) && (p__tmp = ft_split(p__tr[0], ' '));
	if (p__tr && !p__tmp)
		return (-1);
	if (len_2d(p__tmp) > 1)
		(!exit_cmd_f) && (write(2, "exit\n", 6)), ext_err(p__tr[0]),
			free_echoue(p__tmp, len_2d(p__tmp)), free_shell(shell), exit(255);
	free_echoue(p__tmp, len_2d(p__tmp));
	s = ft_get_from_env(&shell->env, ft_strdup("?"));
	(!s) && (malloc_failure(shell, NULL));
	if (len_2d(p__tr) == 0)
		return (free_shell(shell), (!exit_cmd_f) && (write(2, "exit\n", 6)),
			exit_status = ft_atoi(s), free(s), exit(exit_status), 0);
	if (len_2d(p__tr) >= 1)
	{
		if (builtin_exit_soon(shell, p__tr, s, exit_cmd_f) == -1)
			return (free(s), malloc_failure(shell, NULL), -1);
		return (write (2, "exit\nminishell: exit: too many arguments\n", 42),
			free(s), 1);
	}
	return (0);
}
