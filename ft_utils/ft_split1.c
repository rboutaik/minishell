/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:31:59 by rboutaik          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:46 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_tabsize(char const *s, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			size++;
		i++;
	}
	return (size);
}

static int	ft_checkfree(char **tab, char *str, int i)
{
	int	j;

	j = 0;
	if (str == NULL)
	{
		while (j < i)
		{
			free(tab[j]);
			j++;
		}
		free(tab);
		return (1);
	}
	return (0);
}

static char	*ft_setstr(char const *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_iter(char const *s, char c, int k)
{
	int	i;

	i = 0;
	if (k == 1)
	{
		while (*s && *s == c)
		{
			s++;
			i++;
		}
	}
	else
	{
		while (*s && *s != c)
		{
			s++;
			i++;
		}
	}
	return (i);
}

char	**ft_split1(char *s, char c)
{
	char	**tab;
	int		tabsize;
	int		i;

	if (s == NULL)
		return (NULL);
	tabsize = ft_tabsize(s, c);
	tab = (char **)malloc((tabsize + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	s = s + ft_iter(s, c, 1);
	i = -1;
	while (*s && ++i < tabsize + 1)
	{
		if (*s != c)
		{
			tab[i] = ft_setstr(s, c);
			if (ft_checkfree(tab, tab[i], i) == 1)
				return (NULL);
		}
		s = s + ft_iter(s, c, 0);
		s = s + ft_iter(s, c, 1);
	}
	tab[i + 1] = NULL;
	return (tab);
}
