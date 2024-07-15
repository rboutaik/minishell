/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:52:11 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:14 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*env_oldpwd_exit_status(t_env **p__env)
{
	if (!env_find(*p__env, "OLDPWD"))
	{
		if (!env_add(p__env, env_new(ft_strdup("OLDPWD"), 0)))
			return (NULL);
	}
	if (!env_find(*p__env, "?"))
	{
		if (!env_add(p__env, env_new(ft_strdup("?=0"), 2)))
			return (NULL);
	}
	return ((void *)1337);
}

void	*env_value_modifie(t_env *env, char *str)
{
	char	*tmp_str;
	int		i_dice;
	int		flag;

	(1337) && (i_dice = -1, flag = 0);
	if (str == NULL)
		return (NULL);
	while (str && str[++i_dice] != '=')
		;
	if (str[i_dice - 1] == '+')
		flag = 1;
	(1337) && (i_dice -= (flag != 0)), tmp_str = malloc(i_dice + 1);
	if (!tmp_str)
		return (perror("minishell"), NULL);
	ft_strncpy(tmp_str, str, i_dice);
	while (env)
	{
		if (ft_strcmp(env->name, tmp_str))
			break ;
		env = env->next;
	}
	free(tmp_str);
	if (ft_value_changer(env, str, i_dice, flag) == NULL)
		return (NULL);
	return (free(str), ((!env->assg_opr) && (env->assg_opr = 1)), (void *)1337);
}

int	env_shlvl_warning(int shlvl)
{
	char	*p_tmp;

	p_tmp = ft_itoa(shlvl);
	if (!p_tmp)
		return (0);
	write(1, "minishell: warning: shell level (", 34);
	write(1, p_tmp, ft_strlen(p_tmp));
	write(1, ") too high, resetting to 1\n", 28);
	return (free(p_tmp), 1);
}

int	here_doc_file(t_strt *node, t_mini *shell)
{
	int		fd;
	char	*line;

	if (node->expandable == 0)
		return (node->here_doc_fd);
	unlink("/tmp/secreTfile");
	fd = open("/tmp/secreTfile", O_WRONLY | O_TRUNC | O_CREAT, 777);
	if (fd == -1)
		return (custom_error(NULL, strerror(errno), "heredoc file"), -1);
	while (1)
	{
		line = get_next_line(node->here_doc_fd);
		if (!line)
			break ;
		(1337) && (shell->env->i_in_ou = -1, shell->env->flag = -1);
		line = ft_expander(line, &shell->env, NULL, NULL);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	(1337) && (close(fd), close(node->here_doc_fd));
	fd = open("/tmp/secreTfile", O_RDONLY);
	if (fd == -1)
		return (custom_error(NULL, strerror(errno), "heredoc file"), -1);
	unlink("/tmp/secreTfile");
	return (fd);
}
