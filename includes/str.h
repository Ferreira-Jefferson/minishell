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