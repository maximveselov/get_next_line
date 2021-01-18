/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:40:00 by aannett           #+#    #+#             */
/*   Updated: 2021/01/16 19:27:44 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list				*ft_realloc_buff(t_list *list,
size_t pos, size_t len)
{
	char					*tmp;

	if (list->l_buff)
	{
		if (!(tmp = ft_substr_nsfw(list->l_buff, pos, len)))
			return (NULL);
		ft_bzero(list->l_buff, list->b_size);
		free(list->l_buff);
	}
	else
	{
		if (!(tmp = malloc(sizeof(char) * len + 1)))
			return (NULL);
		ft_bzero(tmp, len);
	}
	list->l_buff = tmp;
	list->b_size = len;
	return (list);
}

static t_list				*ft_lstbuild_fd(t_list *list, int fd)
{
	if (!ft_realloc_buff(list, 0, 1024))
		return (NULL);
	list->b_read = 0;
	list->b_written = 0;
	list->filedes = fd;
	list->b_size = 1024;
	return (list);
}

static int					ft_save_newline(char **line, t_list *lst)
{
	char					*ptr;
	char					*tmp;
	size_t					j;

	*line = NULL;
	tmp = NULL;
	if ((ptr = ft_memchr(lst->l_buff, '\n', lst->b_read)))
		j = (size_t)(ptr - ((char*)lst->l_buff + lst->b_written));
	else
		j = lst->b_read - lst->b_written;
	if (!(*line = ft_substr_nsfw(lst->l_buff, 0, j)))
		return (-1);
	lst->b_written = (ptr ? (j + 1) : j);
	if (ptr)
		tmp = ft_substr_nsfw(lst->l_buff, j + 1, lst->b_read - (j + 1));
	ft_bzero(lst->l_buff, lst->b_size);
	lst->b_size = lst->b_read - (j + 1);
	lst->b_read -= j + 1;
	lst->b_written = 0;
	free(lst->l_buff);
	lst->l_buff = tmp;
	if (!ptr)
		return (0);
	return (1);
}

static int					ft_read_buff(t_list *list)
{
	ssize_t					ret;

	if (!(list->s_buff = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	ft_bzero(list->s_buff, BUFFER_SIZE + 1);
	while ((ret = read(list->filedes, list->s_buff, BUFFER_SIZE)))
	{
		if ((list->b_size - list->b_read) < BUFFER_SIZE)
			ft_realloc_buff(list, 0, list->b_size + BUFFER_SIZE + 1024);
		ft_memcpy(list->l_buff + list->b_read, list->s_buff, ret);
		list->b_read += ret;
		if (ft_memchr(list->s_buff, '\n', ret))
			break ;
		ft_bzero(list->s_buff, ret);
	}
	free(list->s_buff);
	ft_realloc_buff(list, 0, list->b_read);
	if (ret < 0 || !list->l_buff)
		return (-1);
	return (1);
}

int							get_next_line(int fd, char **line)
{
	static t_list			node;
	int						rvalue;

	rvalue = 1;
	if (node.filedes != fd)
		ft_lstbuild_fd(&node, fd);
	if (fd < 0 || read(fd, node.l_buff, 0) < 0
		|| BUFFER_SIZE < 1 || !line)
		return (-1);
	if ((!ft_memchr((&node)->l_buff, '\n', node.b_size)
		&& (rvalue = ft_read_buff(&node)) < 0)
		|| (rvalue = ft_save_newline(line, &node)) <= 0)
	{
		node.filedes = -1;
		return (rvalue);
	}
	return (rvalue);
}
