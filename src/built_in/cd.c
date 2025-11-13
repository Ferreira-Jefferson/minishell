#include "built_in.h"

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

	if (args->size  == 1)
		ft_strlcpy(args->head->content, "~", ft_strlen(args->head->content));
	else
		ft_dlstremove_at(args, 0, free);
	if (!args || args->size == 0)
		return (0);
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
	if (errno != 0)
		return (ft_print_error("cd:", node->content, strerror(errno), 1));
	return (0);
}
