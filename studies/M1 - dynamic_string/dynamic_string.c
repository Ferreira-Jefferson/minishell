/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:02:18 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/14 15:25:44 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static inline char *get_buf(t_str *str)
{
	if (!str)
		return (NULL);
	return (str->buf);		
}

static inline t_str *get_str(const char *buf)
{
	if (!buf)
		return (NULL);
	return ((t_str *)(buf - sizeof(t_str)));	
}

char	*str_new(const char *buf)
{
	t_str	*new_str;
	size_t	size;

	if (!buf)
	{
		write(2, "Error: in [str_new] - buf is NULL", 33);
		return (NULL);
	}
	size = ft_strlen(buf);
	new_str = (t_str *) malloc(sizeof(t_str) + size + 1);
	if (!new_str)
	{
		write(2, "Error: in [str_new] - malloc error", 34);
		return (NULL);
	}
	new_str->len = size;
	new_str->capacity = size;
	ft_memcpy(new_str->buf, buf, size);
	new_str->buf[size] = '\0';
	return (new_str->buf);
}

void	str_free(char *buf)
{
	t_str	*to_free;

	if (!buf)
		return ;
	to_free = get_str(buf);
	free(to_free);
}

size_t	str_len(const char *buf)
{
	t_str	*str;

	if (!buf)
		return (0);
	str = get_str(buf);
	if (!str)
		return (0);
	return (str->len);
}

static char *str_make_room(char *buf, size_t addlen)
{
	t_str	*str;
	t_str	*new_str;
	size_t	new_cap;
	size_t	old_size;
	size_t	new_size;

	if (!buf)
		return (NULL);
	if (addlen == 0)
		return (buf);
	str = get_str(buf);
	if (str->capacity >= str->len + addlen)
		return (buf);
	new_cap = (str->len + addlen) * 2;
	old_size = sizeof(t_str) + str->capacity + 1;
	new_size = sizeof(t_str) + new_cap + 1;
	new_str = (t_str *) ft_realloc((void **) &str, old_size, new_size, 1);
	if (!new_str)
		return (buf);
	new_str->capacity = new_cap;
	return (new_str->buf);
}

static char	*str_cat_len(char *buf, const void *s, size_t len)
{
	t_str	*str;

	buf = str_make_room(buf, len);
	if (!buf)
		return (NULL); 
	str = get_str(buf);
	ft_memcpy(buf + str->len, s, len);
	str->len += len;
	buf[str->len] = '\0';
	return (buf);
}

char	*str_cat(char *buf, const char *s)
{
	if (!buf)
		return (NULL);
	if (!s)
		return (buf);
	return (str_cat_len(buf, s, ft_strlen(s)));
}
