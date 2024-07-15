/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_exec_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:19:44 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:02 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	vars_init(t_vars *v)
{
	v->pid = -10;
	v->i_dice_1 = 0;
	v->i_dice_ou = 0;
	v->i_dice_in = 0;
	v->i_dice_redr = 0;
	v->fd_in = 0;
	v->fd_out = 1;
	v->exit_status = 0;
	v->f = 0;
	v->sec_in = -1;
	v->sec_out = -1;
}

int	append_with_cmd(t_strt *node, t_vars *v)
{
	if (ft_in_arr(v->i_dice_ou, node, node->ofile_flag, node->ofile_flag_size))
	{
		custom_error(NULL, "ambiguous redirect", node->ou_file[v->i_dice_ou]);
		return (1);
	}
	else
	{
		if (v->i_dice_ou < (int)len_2d(node->ou_file))
		{
			v->fd_out = open (node->ou_file[v->i_dice_ou++], O_CREAT
					| O_WRONLY | O_APPEND, 0644);
			if (v->fd_out == -1)
			{
				custom_error(NULL, strerror(errno),
					node->ou_file[v->i_dice_ou - 1]);
				return (1);
			}
			if (node->ou_file[v->i_dice_ou])
				close(v->fd_out);
		}
	}
	return (0);
}

int	redir_out_cmd(t_strt *node, t_vars *v)
{
	if (ft_in_arr(v->i_dice_ou, node, node->ofile_flag, node->ofile_flag_size))
	{
		custom_error(NULL, "ambiguous redirect", node->ou_file[v->i_dice_ou]);
		return (1);
	}
	else
	{
		if (v->i_dice_ou < (int)len_2d(node->ou_file))
		{
			v->fd_out = open (node->ou_file[v->i_dice_ou++], O_CREAT
					| O_WRONLY | O_TRUNC, 0644);
			if (v->fd_out == -1)
			{
				custom_error(NULL, strerror(errno),
					node->ou_file[v->i_dice_ou - 1]);
				return (1);
			}
			if (node->ou_file[v->i_dice_ou])
				close(v->fd_out);
		}
	}
	return (0);
}

int	redir_in_cmd(t_strt *node, t_vars *v)
{
	if (ft_in_arr(v->i_dice_in, node, node->ifile_flag, node->ifile_flag_size))
	{
		custom_error(NULL, "ambiguous redirect", node->in_file[v->i_dice_in]);
		return (1);
	}
	else
	{
		if (v->i_dice_in < (int)len_2d(node->in_file))
		{
			v->fd_in = open (node->in_file[v->i_dice_in++], O_RDONLY);
			if (v->fd_in == -1)
			{
				custom_error(NULL, strerror(errno),
					node->in_file[v->i_dice_in - 1]);
				return (1);
			}
			if (node->in_file[v->i_dice_in])
				close(v->fd_in);
		}
	}
	return (0);
}

int	file_with_cmd(t_strt *node, t_vars *v, t_mini *shell, int i)
{
	int	ex_stat;

	ex_stat = 0;
	while (++v->i_dice_1 < node->pr_exec_size && !ex_stat)
	{
		if (node->pr_exec[v->i_dice_1] == APPEND
			&& append_with_cmd(node, v) == 1)
			return (1);
		else if (node->pr_exec[v->i_dice_1] == REDIR)
		{
			if (node->redirect[v->i_dice_redr++][0] == '>'
				&& redir_out_cmd(node, v) == 1)
				return (1);
			else if (node->redirect[v->i_dice_redr - 1][0] == '<'
				&& redir_in_cmd(node, v) == 1)
				return (1);
		}
		else if (node->pr_exec[v->i_dice_1] == HERE_DOC)
		{
			if (!node->delemiter[++i])
				(v->fd_in = here_doc_file(node, shell))
					&& (v->fd_in == -1) && (malloc_failure(shell, NULL));
		}
	}
	return (ex_stat);
}
