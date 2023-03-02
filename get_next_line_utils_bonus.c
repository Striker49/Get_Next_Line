/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:01:25 by seroy             #+#    #+#             */
/*   Updated: 2023/03/02 13:30:47 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	*ft_calloc(size_t count, size_t size)
{
	void	*a;
	size_t	i;

	a = malloc(count * size);
	i = 0;
	if (a == NULL)
		return (NULL);
	while (i < count * size)
	{
		((char *)a)[i] = 0;
		i++;
	}
	return (a);
}

int	ft_strlcpy(char *dst, char *src, int dstsize)
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ts1;
	int		i;
	int		lens1;

	lens1 = ft_strlen(s1);
	if (ft_strchr(s2, '\n') != 0)
		ts1 = (char *)malloc((lens1 + ft_strchr(s2, '\n') + 2) * sizeof(char));
	else
		ts1 = (char *)malloc((lens1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!s2 || !ts1)
		return (NULL);
	i = 0;
	ft_strlcpy(ts1, s1, lens1 + 1);
	while (s2[i] && s2[i] != '\n' && s2[i] != '\0')
	{
		ts1[lens1 + i] = s2[i];
		i++;
	}
	if (s2[i] == '\n')
		ts1[lens1 + i] = s2[i];
	i += (s2[i] == '\n');
	free(s1);
	ts1[lens1 + i] = '\0';
	return (ts1);
}
