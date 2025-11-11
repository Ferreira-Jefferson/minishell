/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:49:27 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/10 10:18:46 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/str.h"

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

static char	*str_make_room(char *buf, size_t addlen)
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
	new_str = (t_str *) malloc(new_size);
	if (!new_str)
		return (buf);
	ft_memcpy(new_str, str, old_size);
	new_str->capacity = new_cap;
	free(str);
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
