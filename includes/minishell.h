/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:41:49 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/11 15:51:18 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>

# include "../lib/libft/include/libft.h"

# include "lexer.h"
# include "ast.h"
# include "hash_table.h"
# include "utils.h"
# include "signals.h"
# include "str.h"
# include "expander.h"
# include "built_in.h"

int		free_str(char *str, int val);
void	free_arr(char **arr);
int		free_ret(t_dlist **list, void *arg, void (*del)(void *), int ret);

#endif
