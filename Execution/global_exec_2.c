/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exec_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:04:32 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:03 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	append_no_cmd(t_strt *node, t_vars *v)
{
	if (ft_in_arr(v->i_dice_ou, node, node->ofile_flag, node->ofile_flag_size))
	{
		custom_error(NULL, "ambiguous redirect", node->ou_file[v->i_dice_ou]);
		return (1);
	}
	else
	{
		v->fd_out = open (node->ou_file[v->i_dice_ou++], O_CREAT
				| O_WRONLY | O_APPEND, 0644);
		if (v->fd_out == -1)
		{
			custom_error(NULL, strerror(errno),
				node->ou_file[v->i_dice_ou - 1]);
			return (1);
		}
		close(v->fd_out);
	}
	return (0);
}

int	redir_out_no_cmd(t_strt *node, t_vars *v)
{
	if (ft_in_arr(v->i_dice_ou, node, node->ofile_flag, node->ofile_flag_size))
	{
		custom_error(NULL, "ambiguous redirect", node->ou_file[v->i_dice_ou]);
		return (1);
	}
	else
	{
		v->fd_out = open (node->ou_file[v->i_dice_ou++], O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
		if (v->fd_out == -1)
		{
			custom_error(NULL, strerror(errno),
				node->ou_file[v->i_dice_ou - 1]);
			return (1);
		}
		close(v->fd_out);
	}
	return (0);
}

int	redir_in_no_cmd(t_strt *node, t_vars *v)
{
	if (ft_in_arr(v->i_dice_in, node, node->ifile_flag, node->ifile_flag_size))
	{
		custom_error(NULL, "ambiguous redirect", node->in_file[v->i_dice_in]);
		return (1);
	}
	else
	{
		v->fd_in = open (node->in_file[v->i_dice_in++], O_RDONLY);
		if (v->fd_in == -1)
		{
			custom_error(NULL, strerror(errno),
				node->in_file[v->i_dice_in - 1]);
			return (1);
		}
		close(v->fd_in);
	}
	return (0);
}

int	file_without_cmd(t_strt *node, t_vars *v)
{
	int	ex_stat;

	ex_stat = 0;
	while (v->i_dice_1 < node->pr_exec_size && !ex_stat)
	{
		if (node->pr_exec[v->i_dice_1] == APPEND
			&& append_no_cmd(node, v) == 1)
			return (1);
		else if (node->pr_exec[v->i_dice_1] == REDIR)
		{
			if (node->redirect[v->i_dice_redr++][0] == '>'
				&& redir_out_no_cmd(node, v) == 1)
				return (1);
			else if (node->redirect[v->i_dice_redr - 1][0] == '<'
				&& redir_in_no_cmd(node, v) == 1)
				return (1);
		}
		else if (node->pr_exec[v->i_dice_1] == HERE_DOC)
			close(node->here_doc_fd);
		v->i_dice_1++;
	}
	return (ex_stat);
}

int	buitins_dup(t_strt *node, t_vars *v, int f, t_mini *shell)
{
	if ((is_build_in(node, shell)
			&& (node->in_file || node->ou_file)) || f)
	{
		v->sec_in = dup(STDIN_FILENO);
		if (v->sec_in == -1)
			return (perror("minishell"), -1);
		v->sec_out = dup(STDOUT_FILENO);
		if (v->sec_out == -1)
			return (close(v->sec_in), perror("minishell"), -1);
		if (dup2(v->fd_in, STDIN_FILENO) == -1)
			return (close(v->sec_in), close(v->sec_out),
				perror("minishell"), -1);
		if (dup2(v->fd_out, STDOUT_FILENO) == -1)
			return (close(v->sec_in), close(v->sec_out),
				close(v->fd_in), perror("minishell"), -1);
		if (v->fd_in != 0)
			close(v->fd_in);
		if (v->fd_out != 1)
			close(v->fd_out);
		v->f = 1;
	}
	return (1);
}
