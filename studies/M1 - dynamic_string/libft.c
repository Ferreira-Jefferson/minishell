#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*aux_dst;
	unsigned char	*aux_src;

	aux_dst = (unsigned char *) dst;
	aux_src = (unsigned char *) src;
	while (len--)
	{
		*aux_dst = *aux_src;
		aux_dst++;
		aux_src++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*aux_dst;
	unsigned char	*aux_src;

	aux_dst = (unsigned char *) dst;
	aux_src = (unsigned char *) src;
	if (aux_dst <= aux_src)
		return (ft_memcpy(aux_dst, aux_src, len));
	while (len--)
		aux_dst[len] = aux_src[len];
	return (dst);
}

void	*ft_to_free(void **p)
{
	if (*p)
	{
		free(*p);
		*p = NULL;
	}
	return (NULL);
}

void	*ft_realloc(void **alloc, size_t cur_sz, size_t new_sz, size_t t_sz)
{
	void	*new_ptr;
	size_t	old_total_bytes;
	size_t	new_total_bytes;
	size_t	copy_size;

	if (!*alloc)
		return (malloc(new_sz * t_sz));
	if (new_sz == 0)
		return (ft_to_free(alloc));
	if (t_sz > 0 && new_sz > (size_t)-1 / t_sz)
		return (NULL);
	new_total_bytes = new_sz * t_sz;
	new_ptr = malloc(new_total_bytes);
	if (!new_ptr)
		return (NULL);
	old_total_bytes = cur_sz * t_sz;
	if (new_total_bytes < old_total_bytes)
		copy_size = new_total_bytes;
	else
		copy_size = old_total_bytes;
	ft_memmove(new_ptr, *alloc, copy_size);
	ft_to_free(alloc);
	return (new_ptr);
}
