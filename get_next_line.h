/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:11:06 by aannett           #+#    #+#             */
/*   Updated: 2021/01/16 19:25:45 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
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

#endif
