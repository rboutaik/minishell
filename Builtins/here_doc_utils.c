/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:07:37 by aachalla          #+#    #+#             */
/*   Updated: 2024/05/29 13:45:10 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	close2(int fd_in, int fd_out)
{
	if (fd_in)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (perror("minishell"), 1);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			return (perror("minishell"), 1);
		close(fd_out);
	}
	return (0);
}

void	custom_error(char *cmd, char *err_msg, char *err_cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (cmd)
		ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
}

int	find(char *s, char *c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c[0] || s[i] == c[1])
			return (1);
		i++;
	}
	return (0);
}

void	vars_init4(t_vars4 *v, int *exit_status, t_mini *shell)
{
	v->fd[0] = -1;
	v->fd[1] = -1;
	v->shell = shell;
	*exit_status = 0;
}

int	ft_in_arr(int n, t_strt *p_tr, int *arr, int size)
{
	int	i;

	i = 0;
	while (p_tr && i < size)
	{
		if (n == arr[i])
			return (1);
		i++;
	}
	return (0);
}
