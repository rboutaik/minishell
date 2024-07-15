/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachalla <aachalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 01:45:39 by rboutaik          #+#    #+#             */
/*   Updated: 2024/05/31 12:42:19 by aachalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ext_err(char *str)
{
	write (2, "minishell: exit: ", 18);
	write (2, str, ft_strlen(str));
	write (2, ": numeric argument required\n", 29);
}

void	*malloc_failure(t_mini *shell, char **str)
{
	free_echoue(str, len_2d(str));
	free_shell(shell);
	exit(-1);
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	size;

	size = 0;
	if (s == NULL || fd < 0 || fd > 1023)
		return ;
	while (s[size])
		size++;
	write(fd, s, size);
}

int	check_empty(t_mini *shell, t_strt *node, char **str, int i)
{
	char	*tmp;

	shell->env->i_in_ou = -1;
	shell->env->flag = -1;
	tmp = ft_expander(ft_strdup(str[i]), &shell->env, node, str[i]);
	if (!tmp)
		malloc_failure(shell, NULL);
	free(node->var_qts);
	node->var_qts = NULL;
	node->var_qts_size = 0;
	node->var_qts_dejavu = 0;
	if (tmp[0] == '\0' && str[i][0] == '$')
		return (free(tmp), 1);
	free(tmp);
	return (0);
}

char	**ft_get_options(t_strt *stack, t_mini *shell, char **tmp, int j)
{
	char	**options;
	int		size;

	size = len_2d(stack->option);
	options = malloc(sizeof(char *) * (size + 2 + (j - 1)));
	if (!options)
		malloc_failure(shell, tmp);
	if (ft_strrchr(stack->command, '/'))
		options[0] = ft_strdup(ft_strrchr(stack->command, '/') + 1);
	else
		options[0] = ft_strdup(stack->command);
	if (options[0] == NULL)
		malloc_failure(shell, tmp);
	return (options);
}
