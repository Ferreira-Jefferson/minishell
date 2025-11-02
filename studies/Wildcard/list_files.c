#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = (const char *) s;
	while (*p)
		p++;
	return (p - s);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_is_numeric(char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

char *ft_get_pid(void)
{
	DIR *dirp;
	struct dirent *dire;

	dirp = opendir("/proc/self/task");
	while (dirp && (dire = readdir(dirp)) != NULL)
		if (ft_is_numeric(dire->d_name))
			break ;
	closedir(dirp);	
	return (dire->d_name);
}

int custom_match(const char *pattern, const char *text)
{
	if (pattern[0] == '*' && ft_strlen(pattern) == 1)
		return (1);
	if (pattern[0] == '.' && text[0] == '.')
		return (1);
	return (1);
}

int main(int argc, char *argv[])
{
	(void) argc;
	DIR *dirp;
	struct dirent *dire;

	int i=0;
	printf("%d : %s\n", getpid(), ft_get_pid());
	char *pattern = "./";
	dirp = opendir(argv[1]);
	printf("dirp: %d [%s]:[%s]\n", dirp == NULL, pattern, argv[1]);
	while (dirp && (dire = readdir(dirp)) != NULL)
	{
		if (dire->d_name[0] == '.' && ft_strlen(dire->d_name) <= 2)
			continue ;
		//if (custom_match(argv[1], dire->d_name))
			//printf("[%d]: [%s] [%d]\n", i++, dire->d_name, dire->d_type);
	}
	closedir(dirp);
	return (0);
}
