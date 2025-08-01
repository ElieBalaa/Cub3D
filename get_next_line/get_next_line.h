/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 01:17:33 by oiskanda          #+#    #+#             */
/*   Updated: 2025/08/01 12:56:49 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	g_strlen(const char *s);
char	*g_strchr(const char *s, int c);
char	*g_strjoin(char *s1, char *s2);
char	*ft_copy_to_newline(char *str);
char	*ft_copy_left_from_buffer(char *str);
char	*get_next_line(int fd);

#endif
