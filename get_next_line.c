/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:57:00 by seroy             #+#    #+#             */
/*   Updated: 2023/02/27 17:47:49 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

	if (!s || ft_strlen(s) - ft_strchr(s, '\n') == 0)
	{
		free(s);
		return (NULL);
	}
	temp = ft_calloc((ft_strlen(s) - ft_strchr(s, '\n') + 1), sizeof(char));
	if (!temp)
	{
		free(s);
		return (NULL);
	}
	i = ft_strchr(s, '\n');
	j = 0;
	while (s[i])
		temp[j++] = s[i++];
	free(s);
	return (temp);
}

// char	*ft_reads(char *buf, char *line, char *over, int reads, int fd)
// {
// 	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// 	if (!buf)
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	while (reads != 0 && ft_strchr(buf, '\n') == 0)
// 	{
// 		reads = read(fd, buf, BUFFER_SIZE);
// 		if (reads == -1 || BUFFER_SIZE == 0)
// 		{
// 			free(buf);
// 			free(over);
// 			over = NULL;
// 			return (NULL);
// 		}
// 		buf[reads] = '\0';
// 		over = ft_strjoin(over, buf);
// 	}
// 	return (over);
// }

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
	line = NULL;;
	if (ft_strchr(over, '\n') != 0)
	{
		line = ft_calloc((ft_strchr(over, '\n') + 1), sizeof(char));
		ft_strlcpy(line, over, (ft_strchr(over, '\n') + 1));
		over = ft_over(over);
		return (line);
	}
	else
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
		{
			free(line);
			return (NULL);
		}
		while (reads != 0 && ft_strchr(buf, '\n') == 0)
		{
			reads = read(fd, buf, BUFFER_SIZE);
			if (reads == -1 || BUFFER_SIZE == 0)
			{
				free(buf);
				free(over);
				over = NULL;
				return (NULL);
			}
			buf[reads] = '\0';
			over = ft_strjoin(over, buf);
		}
		if (ft_strchr(over, '\n'))
			line = ft_calloc((ft_strchr(over, '\n') + 1), sizeof(char));
		else
			line = ft_calloc((ft_strlen(over) + 1), sizeof(char));
		ft_strlcpy(line, over, (ft_strlen(over) + 1));
		free(over);
		over = ft_over(buf);
	}
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}


// #include <unistd.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("Notes.txt", O_RDONLY);
// 	for (int i = 0; i < 6; i++)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }
