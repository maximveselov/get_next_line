/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:11:06 by aannett           #+#    #+#             */
/*   Updated: 2021/01/15 16:57:34 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct		s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	void			*l_buff;
	void			*s_buff;
	int				filedes;
	size_t			b_read;
	size_t			b_written;
	size_t			b_size;
	size_t			read_ret;
}					t_list;
int					get_next_line(int fd, char **line);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_substr_nsfw(const char *s, unsigned int pos,
size_t len);
t_list				*ft_realloc_buff(t_list **list, size_t pos, size_t len);
#endif
