/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:47:35 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/17 11:10:16 by jtertuli         ###   ########.fr       */
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
	char	buf[]; // "Flexible Array Member" (FAM)
}	t_str;

void	str_free(char *buf);
size_t	str_len(const char *buf);
char	*str_new(const char *init);
char	*str_cat(char *buf, const char *s);

#endif