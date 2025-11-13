#include "minishell.h"

static void	ft_set_rl_propmt(t_shell_context *sc)
{
	char	*home;
	char	*tmp;
	char	*has_home;

	home = ht_search(sc->env, "HOME");
	if (ft_strcmp(sc->pwd, home) == 0)
		sc->rl_prompt = str_cat(sc->rl_prompt, ":~$ ");
	else
	{
		tmp = ft_strdup(sc->pwd);
		sc->rl_prompt = str_cat(sc->rl_prompt, ":~");
		has_home = ft_strnstr(sc->pwd, home, str_len(sc->pwd));
		if (has_home)
		{
			free(tmp);
			tmp = ft_substr(sc->pwd, str_len(home), str_len(sc->pwd));
		}
		sc->rl_prompt = str_cat(sc->rl_prompt, tmp);
		sc->rl_prompt = str_cat(sc->rl_prompt, "$ ");
		free(tmp);
	}
	str_free(home);
}

void	ft_define_rl_prompt(t_shell_context *sc)
{
	char	*session_manager;
	char	*tmp;

	if (sc->rl_prompt)
		str_free(sc->rl_prompt);
	sc->rl_prompt = ht_search(sc->env, "USER");
	sc->rl_prompt = str_cat(sc->rl_prompt, "@");
	session_manager = ht_search(sc->env, "SESSION_MANAGER");
	tmp = ft_strchr(session_manager, '/') + 1;
	tmp[ft_strchr(tmp, '.') - tmp] = '\0';
	sc->rl_prompt = str_cat(sc->rl_prompt, tmp);
	ft_set_rl_propmt(sc);
	str_free(session_manager);
}

int	ft_getpid(void)
{
	DIR				*dirp;
	struct dirent	*dire;
	int				pid;

	dirp = opendir("/proc/self/task");
	if (!dirp)
		return (0) ;	
	dire = readdir(dirp);
	if (!dire)
		return (0) ;
	while (dire)
	{
		if (ft_is_numeric(dire->d_name))
			break ;
		dire = readdir(dirp);
	}
	pid = ft_atoi(dire->d_name);
	closedir(dirp);
	return (pid);
}

t_shell_context	*ft_setup_sc(char **envp)
{
	t_shell_context	*sc;

	sc = (t_shell_context *) malloc(sizeof(t_shell_context));
	sc->pid_ms = ft_getpid();
	sc->ast_root = NULL;
	sc->env = env_load(envp);
	sc->env_copy = env_load(envp);
	sc->pwd = ht_search(sc->env, "PWD");
	sc->rl_prompt = NULL;
	sc->fds = ft_dlstinit();
	sc->last_status = 0;
	return (sc);
}

