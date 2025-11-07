#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"

char	*b_env(t_shell_context *sc);
void	b_export(t_shell_context *sc);
void	b_set_export(t_shell_context *sc, t_dlist	*args);
void	b_echo(t_shell_context *sc, t_dlist	*args);
void	b_uset(t_shell_context *sc, t_dlist	*args);

// export_utils.c
char	*sort_export(char *str_export, int i, int j);
int		ft_isvalid_key(char *key);

#endif