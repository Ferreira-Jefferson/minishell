#include "built_in.h"

int	b_pwd(t_shell_context *sc, t_dlist	*args)
{
	(void) args;
	if (!sc || !args)
		return (1);
	if (!sc->pwd)
		return (1);
	printf("%s\n", sc->pwd);
	return (0);
}