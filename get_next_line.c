/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:57:00 by seroy             #+#    #+#             */
/*   Updated: 2023/02/24 17:14:35 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_free(char *s)
{
	free(s);
	return (NULL);
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

char	*ft_over(char *s)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	temp = NULL;
	if (ft_strchr(s, '\n') != 0)
	{
		while (s[i] != '\n')
			i++;
		i++;
	}
	temp = ft_calloc((ft_strlen(s) - i + 1), sizeof(char));
	if (!temp)
		return (NULL);
	j = 0;
	while (s[i])
	{
		temp[j] = s[i];
		i++;
		j++;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	int					i;
	int					reads;
	char				*buf;
	char				*line;
	static char			*over;

	i = 0;
	reads = 1;
	buf = NULL;
	line = NULL;
	if (ft_strchr(over, '\n') != 0)
	{
		line = ft_calloc((ft_strchr(over, '\n') + 1), sizeof(char));
		ft_strlcpy(line, over, (ft_strchr(over, '\n') + 1));
		over = ft_over(over);
		return (line);
	}
	else
	{
		if (ft_strchr(over, '\n') == 0)
		{
			line = ft_calloc((ft_strlen(over) + 1), sizeof(char));
			ft_strlcpy(line, over, (ft_strlen(over) + 1));
			ft_free(over);
		}
		while (reads != 0 && ft_strchr(buf, '\n') == 0)
		{
			buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
			if (!buf)
				ft_free(buf);
			reads = read(fd, buf, BUFFER_SIZE);
			if (reads == -1 || BUFFER_SIZE == 0)
				return (NULL);
			line = ft_strjoin(line, buf);
		}
		over = ft_over(buf);
		ft_free(buf);
	}
	return (line);
}


#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("1.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}
