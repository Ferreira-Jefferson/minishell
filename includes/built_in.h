#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "minishell.h"
# include "utils.h"

int		b_env(t_shell_context *sc, t_dlist *args);
int		b_export(t_shell_context *sc, t_dlist *args);
int		b_set_export(t_shell_context *sc, t_dlist *args);
int		b_echo(t_shell_context *sc, t_dlist *args);
int		b_unset(t_shell_context *sc, t_dlist *args);
int		b_pwd(t_shell_context *sc, t_dlist *args);
int		b_cd(t_shell_context *sc, t_dlist *args);
int		b_exit(t_shell_context *sc, t_dlist *args);

// export_utils.c
char	*sort_export(char *str_export);
int		ft_isvalid_key(char *key);

#endif