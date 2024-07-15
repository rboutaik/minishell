/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboutaik <rboutaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:44:42 by aachalla          #+#    #+#             */
/*   Updated: 2024/06/02 19:31:50 by rboutaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_sstrcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i + 1] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char )s2[i]);
}

char	*ft_strnstr(const char *haystack, char *needle, int len)
{
	int	i;
	int	ns;

	ns = ft_strlen(needle);
	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_sstrcmp(needle, &haystack[i]) == 0
				&& ns + i <= len)
				return (((char *)&haystack[i]));
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	int		i;
	char	*str;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	else if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (perror("minishell"), NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	i = -1;
	j = ft_strlen(s1);
	while (s2[++i])
		str[i + j] = s2[i];
	str[i + j] = '\0';
	return (str);
}

char	*ft_strrchr(char *s, int c)
{
	char	x;
	int		loc;
	int		i;

	x = (char )c;
	loc = -1;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == x)
			loc = i;
		i++;
	}
	if (s[i] == x)
		return ((char *)s + i);
	else if (loc != -1)
		return ((char *)s + loc);
	return (NULL);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	int		j;
	char	*newstr;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (newstr == NULL)
		return (perror("minishell"), NULL);
	i = start + len;
	j = 0;
	while (start < i && s[start])
	{
		newstr[j] = s[start];
		start++;
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}
