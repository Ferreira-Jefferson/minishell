#ifndef UTILS_H
# define UTILS_H

t_hash_table	*env_load(char **envp);
char			*ft_str_toupper(char *str);
void			ft_free_str_vector(char **str_vector);

#endif