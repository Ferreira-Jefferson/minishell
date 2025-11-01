#include "expander.h"

// static void	ex_handler_wildcard(t_shell_context *sc, char **new_str, char *key)
// {
	
// }	

void	ex_wildcard(t_shell_context *sc, char *content, \
	char **new_str, int start_quotes)
{
	char	str_tmp[2];
	size_t	index;

	(void) sc;
	(void) new_str;
	(void) start_quotes;
	(void) str_tmp;
	(void) index;

	index = 0;
	char **content_split = ft_split(content, ' ');

	while (*content_split)
	{
		if (ft_strchr(*content_split, '*'))
		{
			printf("Splite: [%s]\n", *content_split);
		}
		content_split++;
	}
}