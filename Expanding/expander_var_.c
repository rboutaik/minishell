/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:47:57 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:00 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*vars_init_2(t_vars2 *v, t_vars3 *v3, char *s)
{
	v->echo_flag = 0;
	v->i = 0;
	v->j = 0;
	if (!s)
		return (NULL);
	v->var = ft_substr(s, v3->start, v3->end - v3->start);
	if (!v->var)
		return (NULL);
	v->exp_var = ft_strjoin("$", v->var);
	v->size = ft_strlen(v->var) + 1;
	v->var = ft_get_from_env(v3->env, v->var);
	if (!v->exp_var || !v->var)
		return (free(v->exp_var), NULL);
	v->ss = ft_strlen(v->var) - 1;
	v->tmp = ft_split1(v->var, ' ');
	if (!v->tmp)
		return (free(v->exp_var), free(v->var), NULL);
	return ((void *)1337);
}

void	vars_init_3(t_vars3 *v3, t_env **env, char *expanded_var, char *s)
{
	v3->start = -1;
	v3->end = -1;
	v3->expanded_var = expanded_var;
	if (!*env)
	{
		v3->n = -1;
		v3->f = -1;
	}
	else
	{
		v3->n = (*env)->i_in_ou;
		v3->f = (*env)->flag;
	}
	v3->env = env;
	v3->var_size = 0;
	v3->str = s;
	v3->new_line = 0;
}

void	var_end(char *p, t_vars3 *v3, int *i)
{
	v3->start = *i;
	if (ft_isdigit(p[*i]) || (p[*i] == '?'))
		v3->end = *i + 1;
	else
	{
		while (p[*i] && (aln(p[*i]) || p[*i] == '_' ))
			(*i)++;
		v3->end = *i;
	}
}

int	check_pipe(t_strt *p_stack)
{
	t_strt	*node;

	node = p_stack;
	while (node && node->type != HERE_DOC && !node->here_doc)
		node = node->next;
	while (node)
	{
		if (node->type == PIPE)
			return (1);
		node = node->prev;
	}
	return (0);
}

int	hrd_ex(t_mini *shell, t_strt *node, int ex_st)
{
	int		hdrc_dice;
	int		hdrc_stat;
	int		i;

	while (node)
	{
		(1337) && (hdrc_dice = 0, i = 0);
		if (node->type == HERE_DOC || node->here_doc)
		{
			while (node->here_doc[i])
			{
				hdrc_stat = execute_here_doc(node, &ex_st, hdrc_dice++, shell);
				(hdrc_stat == -1) && (malloc_failure(shell, NULL));
				if (hdrc_stat)
					return (close(node->here_doc_fd), hdrc_stat);
				i++;
				(node->here_doc[i]) && (close(node->here_doc_fd));
			}
		}
		else if (node->type == CH_MD && hrd_ex(shell, node->chil_cmd, 0))
			return (1337);
		node = node->next;
	}
	return (ex_st);
}
