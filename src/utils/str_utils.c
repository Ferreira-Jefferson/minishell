/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:50:37 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/30 10:49:16 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/str.h"

static inline t_str	*get_str(const char *buf)
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
		return (NULL);
	size = ft_strlen(buf);
	new_str = (t_str *) malloc(sizeof(t_str) + size + 1);
	if (!new_str)
		return (NULL);
	new_str->len = size;
	new_str->capacity = size;
	ft_memcpy(new_str->buf, buf, size);
	new_str->buf[size] = '\0';
	return (new_str->buf);
}

char *str_replace(char *buf, const char *str)
{
	if (!buf)
		return (NULL);
	str_free(buf);
	return (str_new(str));
}

void	str_free(char *buf)
{
	t_str	*to_free;

	if (!buf)
		return ;
	to_free = get_str(buf);
	free(to_free);
}
