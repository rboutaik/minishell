/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:39:51 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:41 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_allocat2(int size, char **s1, char **s2)
{
	char	*str;

	str = (char *)malloc((size + 1) * sizeof(char));
	if (str == NULL)
	{
		if (*s1)
		{
			free(*s1);
			*s1 = NULL;
		}
		if (*s2)
			free(*s2);
		return (NULL);
	}
	return (str);
}

char	*ft_allocat(char **str, int s)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (s + 1));
	if (!buffer)
	{
		if (*str)
		{
			free(*str);
			*str = NULL;
		}
		return (NULL);
	}
	return (buffer);
}

int	f(char **str, char **buffer, int size)
{
	if (size == 0)
	{
		free(*buffer);
		if (*str)
			return (0);
		else
			return (1);
	}
	else if (size == -1)
	{
		if (*str)
		{
			free(*str);
			*str = NULL;
		}
		free(*buffer);
		return (2);
	}
	return (3);
}

char	*get_next_line(int fd)
{
	int			size;
	char		*buffer;
	static char	*str;
	int			v;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483646)
		return (NULL);
	while (!ft_strchrr(str, '\n'))
	{
		buffer = ft_allocat(&str, BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		size = read(fd, buffer, BUFFER_SIZE);
		v = f(&str, &buffer, size);
		if (v == 0)
			break ;
		else if (v == 1 || v == 2)
			return (NULL);
		buffer[size] = '\0';
		str = ft_strjoinn(str, buffer);
	}
	buffer = ft_getstrr(str);
	if (!buffer)
		return (free(str), str = NULL, NULL);
	return (str = ft_getsecondd(str), buffer);
}
