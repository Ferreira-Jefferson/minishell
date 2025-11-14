/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:59:04 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 08:59:05 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stdlib.h>
# include <unistd.h>

# include "minishell.h"

typedef struct s_str {
	size_t	len;
	size_t	capacity;
	char	buf[];
}	t_str;

t_str	*get_str(const char *buf);
void	str_free(char *buf);
size_t	str_len(const char *buf);
char	*str_new(const char *init);
char	*str_cat(char *buf, const char *s);
char	*str_replace(char *buf, const char *str);
char	*str_clear(char *buf);

#endif