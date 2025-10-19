#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include "str.h"

void	*ft_to_free(void **p);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_realloc(void **alloc, size_t cur_sz, size_t new_sz, size_t t_sz);

#endif