/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:57:00 by seroy             #+#    #+#             */
/*   Updated: 2023/03/02 13:57:38 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (NULL);
}

char	*fover(char *s)
{
	int		i;
	int		j;
	char	*temp;

	if (!s || ft_strlen(s) - ft_strchr(s, '\n') == 0)
	{
		ft_free(s);
		return (NULL);
	}
	temp = ft_calloc((ft_strlen(s) - ft_strchr(s, '\n') + 1), sizeof(char));
	if (!temp)
	{
		ft_free(s);
		return (NULL);
	}
	i = ft_strchr(s, '\n');
	j = 0;
	while (s[i])
		temp[j++] = s[i++];
	ft_free(s);
	return (temp);
}

char	*ft_reads(int fd, int reads, char *buf, char *over)
{
	while (reads != 0 && ft_strchr(buf, '\n') == 0)
	{
		reads = read(fd, buf, BUFFER_SIZE);
		if (reads == -1 || BUFFER_SIZE == 0)
		{
			ft_free(buf);
			ft_free(over);
			over = NULL;
			return (NULL);
		}
		buf[reads] = '\0';
		over = ft_strjoin(over, buf);
	}
	return (over);
}

char	*nl(char *over)
{
	char	*line;

	line = ft_calloc((ft_strchr(over, '\n') + 1), sizeof(char));
	ft_strlcpy(line, over, (ft_strchr(over, '\n') + 1));
	return (line);
}

char	*get_next_line(int fd)
{
	t_struct		gnl;
	static char		*over[OPEN_MAX];

	gnl.reads = 1;
	gnl.line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE == 0)
		return (NULL);
	if (ft_strchr(over[fd], '\n') != 0)
		return (gnl.line = nl(over[fd]), over[fd] = fover(over[fd]), gnl.line);
	gnl.buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!gnl.buf)
		return (ft_free(gnl.buf));
	over[fd] = ft_reads(fd, gnl.reads, gnl.buf, over[fd]);
	if (gnl.reads == -1 || BUFFER_SIZE == 0 || !over[fd])
		return (NULL);
	if (ft_strchr(over[fd], '\n'))
		gnl.line = ft_calloc((ft_strchr(over[fd], '\n') + 1), sizeof(char));
	else
		gnl.line = ft_calloc((ft_strlen(over[fd]) + 1), sizeof(char));
	ft_strlcpy(gnl.line, over[fd], (ft_strlen(over[fd]) + 1));
	ft_free(over[fd]);
	over[fd] = fover(gnl.buf);
	if (!*gnl.line)
		return (ft_free(gnl.line));
	return (gnl.line);
}

// #include <unistd.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("random.txt", O_RDONLY);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
