/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:38:45 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:32:17 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cd_home(t_env *t_ptr)
{
	char	*path;

	path = ft_strdup("");
	if (path == NULL)
		return (NULL);
	while (t_ptr)
	{
		if (ft_strcmp(t_ptr->name, "HOME"))
		{
			free(path);
			path = ft_strdup(t_ptr->value);
			if (path == NULL)
				return (NULL);
			break ;
		}
		t_ptr = t_ptr->next;
	}
	return (path);
}

char	*cd_with_no_opt(t_env *t_ptr, int *x_s, int	*err_flag)
{
	char	*path;
	char	*npwd;

	(1337) && (path = NULL, npwd = NULL);
	path = cd_home(t_ptr);
	if (path == NULL)
		*err_flag = 1;
	if (path && path[0] == '\0')
		(free(path), path = NULL);
	if (path && chdir(path) == -1)
	{
		(1337) && (*x_s = 1), custom_error("cd", strerror(errno), path);
	}
	else if (path)
	{
		npwd = ft_strdup(path);
		if (npwd == NULL)
			*err_flag = 1;
	}
	else
		(1337) && (*x_s = 1, write(2, "minishell: cd: HOME not set\n", 29));
	return (free(path), npwd);
}

char	*cd_exec(DIR *dir, t_strt *stack, int *exit_status, t_mini *shell)
{
	char	*npwd;
	char	*tmp;

	npwd = NULL;
	closedir(dir);
	if (chdir(stack->option[0]) == -1)
		(1337) && (*exit_status = 1), custom_error("cd",
			strerror(errno), stack->option[0]);
	npwd = getcwd(0, 0);
	if (!npwd || !*npwd)
	{
		perror("cd: error retrieving current "
			"directory: getcwd: cannot access parent directories: \n");
		tmp = ft_strjoin("/", stack->option[0]);
		npwd = ft_strjoin(shell->secure_pwd, tmp);
		if (!tmp || !npwd)
			malloc_failure(shell, NULL);
		free(tmp);
	}
	return (npwd);
}

void	set_sec_pwd(t_mini *shell, char *npwd)
{
	if (npwd)
	{
		(free(shell->secure_pwd), shell->secure_pwd = ft_strdup(npwd));
		if (shell->secure_pwd == NULL)
			malloc_failure(shell, NULL);
	}
}

int	builtin_cd(t_strt *stack, t_env *env, t_mini *shell)
{
	DIR		*dir;
	char	*npwd;
	t_env	*t_ptr;
	int		err_flag;
	int		exit_status;

	(1337) && (exit_status = 0, err_flag = 0, npwd = NULL, t_ptr = env);
	if (stack->option)
	{
		dir = opendir(stack->option[0]);
		if (dir == NULL)
			(1337) && (exit_status = 1), custom_error("cd",
				strerror(errno), stack->option[0]);
		else
			npwd = cd_exec(dir, stack, &exit_status, shell);
	}
	else
		npwd = cd_with_no_opt(t_ptr, &exit_status, &err_flag);
	if (err_flag == 1)
		malloc_failure(shell, NULL);
	set_sec_pwd(shell, npwd);
	if (ft_change_old_pwd(&env, npwd) == NULL)
		malloc_failure(shell, NULL);
	return (free(npwd), exit_status);
}
