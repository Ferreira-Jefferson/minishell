/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:30:52 by jtertuli          #+#    #+#             */
/*   Updated: 2025/10/14 13:42:32 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
