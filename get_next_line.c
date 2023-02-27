/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:57:00 by seroy             #+#    #+#             */
/*   Updated: 2023/02/27 12:36:57 by seroy            ###   ########.fr       */
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
	if (!s)
		return (NULL);	
	if (ft_strchr(s, '\n') != 0)
	{
		while (s[i] != '\n')
			i++;
		i++;
	}
	else
		while (s[i])
			i++;
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
	free(s);
	return (temp);
}

char	*put_over(char *over, char *line)
{
	// if (ft_strchr(over, '\n') != 0)
	// {
	// 	line = ft_calloc((ft_strchr(over, '\n') + 1), sizeof(char));
	// 	ft_strlcpy(line, over, (ft_strchr(over, '\n') + 1));
	// 	over = ft_over(over);
	// }
	// else
	{
		line = ft_calloc((ft_strlen(over) + 1), sizeof(char));
		ft_strlcpy(line, over, (ft_strlen(over) + 1));
		over = ft_free(over);
	}
	return (line);
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
		}
		while (reads != 0 && ft_strchr(buf, '\n') == 0)
		{
			buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
			if (!buf)
				free(buf);
			reads = read(fd, buf, BUFFER_SIZE);
			if (reads == -1 || BUFFER_SIZE == 0)
				return (NULL);
			line = ft_strjoin(line, buf);
			// if (ft_strchr(buf, '\n') == 0)
			// 	free(buf);
		}			

		over = ft_over(buf);
		// if (reads == 0)
		// 	free(buf);
	}
	if (reads == 0 && !*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}


#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	for (int i = 0; i < 5; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	return (0);
}
