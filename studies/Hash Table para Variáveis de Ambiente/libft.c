#include "minishell.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*aux;

	aux = dest;
	while (len--)
	{
		*aux = (unsigned char) c;
		aux++;
	}
	return (dest);
}

void	*ft_calloc(size_t number, size_t size)
{
	void	*p;

	if (!size || !number)
		return (malloc(1));
	if (size && number > (size_t)-1 / size)
		return (NULL);
	p = (void *) malloc(number * size);
	if (!p)
		return (NULL);
	p = ft_memset(p, 0, number * size);
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

int	ft_isequal(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (*s1)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}