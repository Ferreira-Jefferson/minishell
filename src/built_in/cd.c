/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:08:18 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/15 16:01:16 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	sc->cmd = str_replace(sc->cmd, "cd:");
	ft_dlstremove_at(args, 0, free);
	if (args->size == 0)
		return (0);
	if (args->size > 1)
		return (ft_print_error(sc, "", "too many arguments", 1));
	to_free = ft_create_content(args);
	node = ft_dlstnew(to_free);
	expander(sc, node);
	path = ft_strtrim(node->content, " 	");
	status = chdir(path);
	if (status == 0)
		ft_set_paths(sc);
	else if (errno != 0)
		ft_print_error(sc, node->content, strerror(errno), errno);
	free(path);
	str_free(to_free);
	ft_dlstdelone(node, free);
	return (errno);
}
