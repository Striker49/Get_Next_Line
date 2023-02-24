/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:01:25 by seroy             #+#    #+#             */
/*   Updated: 2023/02/24 17:07:21 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(const char *s, int c)
{
	unsigned long int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if ((unsigned char)c == s[i])
		{
			i++;
			return (i);
		}
		i++;
	}
	if (s[i] == '\0' && (unsigned char)c == '\0')
		return (i);
	return (0);
}

char	*ft_substr(char *s, int start)
{
	char	*s2;
	int		nlen;

	if (!s)
		return (NULL);
	nlen = ft_strlen(s);
	s2 = (char *)malloc((nlen + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s + start, nlen + 1);
	return (s2);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(src);
	if (!src || !dst)
		return (0);
	if (dstsize == 0)
		return (j);
	while (src[i] && i < dstsize - 1 && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dst[i] = '\n';
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (j);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*ts1;
	int		i;
	int		lens1;
	int		lens2;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	ts1 = (char *)malloc((lens1 + lens2 + 1) * sizeof(char));
	// if (!s1 || !s2 || !ts1)
	if (!s2 || !ts1)
		return (NULL);
	i = 0;
	while ( s1[i] && s1[i] != '\0')
	{
		ts1[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] && s2[i] != '\n')
	{
		ts1[lens1 + i] = s2[i];
		i++;
	}
	if (s2[i] == '\n')
		ts1[lens1 + i] = s2[i];
	return (ts1);
}
