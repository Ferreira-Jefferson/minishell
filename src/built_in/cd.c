#include "built_in.h"

static int	ft_handler_error(t_shell_context *sc, char *message)
{
	sc->last_status = errno;
	if (errno)
	{
		perror(message);
		return (1);
	}
	return (0);
}

static void	ft_set_paths(t_shell_context *sc)
{
	char	*pwd;
	char	new_pwd[1024];

	pwd = ht_search(sc->env, "PWD");
	ht_update_insert(sc->env, "OLDPWD", pwd, ENV);
	if (getcwd(new_pwd, sizeof(new_pwd)) != NULL)
	{
		str_free(pwd);
		ht_update_insert(sc->env, "PWD", new_pwd, ENV);
		pwd = ht_search(sc->env, "PWD");
		sc->pwd = str_replace(sc->pwd, pwd);
	}
	str_free(pwd);
}

int	b_cd(t_shell_context *sc, t_dlist	*args)
{
	t_dnode	*node;
	int		status;
	char	*path;
	char	*to_free;

	ft_dlstremove_at(args, 0, free);
	node = ft_dlstnew("");
	node->content = ft_create_content(args);
	to_free = node->content;
	expander(sc, node);
	path = ft_strtrim(node->content, " 	");
	status = chdir(path);
	if (status == 0)
		ft_set_paths(sc);
	free(path);
	str_free(to_free);
	ft_dlstdelone(node, free);
	return (ft_handler_error(sc, "cd"));
}
