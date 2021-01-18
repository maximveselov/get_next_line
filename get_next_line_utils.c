/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aannett <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 15:23:29 by aannett           #+#    #+#             */
/*   Updated: 2021/01/16 19:26:02 by aannett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				ft_bzero(void *s, size_t n)
{
	unsigned char	*ret;

	ret = s;
	while (n--)
	{
		*ret = 0;
		ret++;
	}
}

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ret;
	size_t			i;

	ret = (unsigned char*)s;
	i = 0;
	while (i < n)
	{
		if (ret[i] == (unsigned char)c)
			return ((void*)&ret[i]);
		i++;
	}
	return (NULL);
}

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ret;
	unsigned char	*inp;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	ret = dst;
	inp = (unsigned char*)src;
	ret[n] = 0;
	while (i < n)
	{
		ret[i] = inp[i];
		i++;
	}
	return (ret);
}

char				*ft_substr_nsfw(const char *s, unsigned int pos, size_t len)
{
	char			*ret;
	size_t			i;

	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (s)
	{
		while (i < len && s[i + pos] != 0)
		{
			ret[i] = s[i + pos];
			i++;
		}
	}
	ret[i] = 0;
	return (ret);
}
