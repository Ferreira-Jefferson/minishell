#ifndef EXPANDER_H
# define EXPANDER_H

#include "minishell.h"

char	*ex_get_key(char *str);
int		ex_get_value_variable(t_shell_context *sc, char **new_str, char *key);
int		ex_question_mark(t_shell_context *sc, char **new_str);
int		ex_double_dollar(t_shell_context *sc, char **new_str);
void	expander(t_shell_context *sc, t_dnode *node);

#endif