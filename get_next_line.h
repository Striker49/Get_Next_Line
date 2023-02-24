/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seroy <seroy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:58:01 by seroy             #+#    #+#             */
/*   Updated: 2023/02/24 17:09:22 by seroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>

// studio
# include <stdio.h>


#ifndef BUFFER_SIZE
// #define BUFFER_SIZE 1
#define BUFFER_SIZE 1000
#endif

char	*get_next_line(int fd);
char	*ft_substr(char *s, int start);
int		ft_strlen(const char *str);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strchr(const char *s, int c);

#endif