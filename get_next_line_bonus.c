/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:40:00 by aannett           #+#    #+#             */
/*   Updated: 2021/01/16 19:30:51 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list				*ft_lstbuild_fd(t_list **list, int fd)
{
	t_list					*ret;

	if (!(ret = malloc(sizeof(t_list))))
		return (NULL);
	ret->l_buff = NULL;
	ft_realloc_buff(&ret, 0, 1024);
	ret->b_read = 0;
	ret->b_written = 0;
	ret->filedes = fd;
	ret->b_size = 1024;
	ret->next = NULL;
	ret->prev = NULL;
	if (*list)
	{
		ret->prev = *list;
		(*list)->next = ret;
		*list = (*list)->next;
	}
	else
		*list = ret;
	return (ret);
}

static t_list				*ft_lstmanage_fd(t_list **first, int fd)
{
	t_list					*ptr;

	ptr = NULL;
	if (*first)
	{
		ptr = *first;
		while (ptr)
		{
			if (ptr->filedes == fd)
				return (ptr);
			if (!ptr->next)
				break ;
			ptr = ptr->next;
		}
		if (!(ft_lstbuild_fd(&ptr, fd)))
			return (NULL);
	}
	else
	{
		if (!(ft_lstbuild_fd(first, fd)))
			return (NULL);
		ptr = *first;
	}
	return (ptr);
}

static int					ft_save_newline(char **line, t_list **lst)
{
	char					*ptr;
	char					*tmp;
	size_t					j;

	*line = NULL;
	tmp = NULL;
	if ((ptr = ft_memchr((*lst)->l_buff, '\n', (*lst)->b_read)))
		j = (size_t)(ptr - ((char*)(*lst)->l_buff + (*lst)->b_written));
	else
		j = (*lst)->b_read - (*lst)->b_written;
	if (!(*line = ft_substr_nsfw((*lst)->l_buff, 0, j)))
		return (-1);
	(*lst)->b_written = (ptr ? (j + 1) : j);
	if (ptr)
		tmp = ft_substr_nsfw((*lst)->l_buff, j + 1, (*lst)->b_read - (j + 1));
	ft_bzero((*lst)->l_buff, (*lst)->b_size);
	(*lst)->b_size = (*lst)->b_read - (j + 1);
	(*lst)->b_read -= j + 1;
	(*lst)->b_written = 0;
	free((*lst)->l_buff);
	(*lst)->l_buff = tmp;
	if (!ptr)
		return (0);
	return (1);
}

static int					ft_read_buff(t_list **list)
{
	ssize_t					ret;

	if (!((*list)->s_buff = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	ft_bzero((*list)->s_buff, BUFFER_SIZE + 1);
	while ((ret = read((*list)->filedes, (*list)->s_buff, BUFFER_SIZE)))
	{
		if (((*list)->b_size - (*list)->b_read) < BUFFER_SIZE)
			ft_realloc_buff(list, 0, (*list)->b_size + BUFFER_SIZE + 1024);
		ft_memcpy((*list)->l_buff + (*list)->b_read, (*list)->s_buff, ret);
		(*list)->b_read += ret;
		if (ft_memchr((*list)->s_buff, '\n', ret))
			break ;
		ft_bzero((*list)->s_buff, ret);
	}
	free((*list)->s_buff);
	ft_realloc_buff(list, 0, (*list)->b_read);
	if (ret < 0 || !(*list)->l_buff)
		return (-1);
	return (1);
}

int							get_next_line(int fd, char **line)
{
	static t_list			*head;
	t_list					*node;
	int						rvalue;

	rvalue = 1;
	if (fd < 0 || !(node = ft_lstmanage_fd(&head, fd)) ||
		read(fd, node->s_buff, 0) < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if ((!ft_memchr(node->l_buff, '\n', node->b_size)
		&& (rvalue = ft_read_buff(&node)) < 0)
		|| (rvalue = ft_save_newline(line, &node)) <= 0)
	{
		if (node->prev)
			node->prev->next = node->next;
		if (node->next)
			node->next->prev = node->prev;
		if (node == head)
			head = head->next;
		free(node);
		node = NULL;
		return (rvalue);
	}
	return (rvalue);
}
