/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaolive <joaolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:42:40 by joaolive          #+#    #+#             */
/*   Updated: 2025/11/12 15:48:50 by joaolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	str_hex(char *dest, unsigned char *str, int n)
{
	unsigned char	byte;
	char			*hex_base;
	int				i;
	int				j;

	hex_base = "0123456789abcdef";
	i = 0;
	j = 0;
	while (i < n)
	{
		byte = str[i];
		dest[j] = hex_base[((byte >> 4) & 0xF)];
		dest[j + 1] = hex_base[byte & 0x0F];
		i++;
		j += 2;
	}
}

char	*gen_filename(void)
{
	unsigned char	buffer[8];
	char			*filename;
	int				fd;
	int				bytes_read;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, buffer, 8);
	close(fd);
	if (bytes_read != 8)
		return (NULL);
	filename = ft_calloc(17, sizeof(char));
	if (!filename)
		return (NULL);
	str_hex(filename, buffer, 8);
	return (filename);
}
