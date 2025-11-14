/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_wildcard_sort.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:56:20 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 15:57:10 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	aux_sort_file_name(char	**split, int i, int j)
{
	char	*str_aux[2];
	char	*tmp;

	while (split[j])
	{
		str_aux[0] = ft_str_toupper(split[i]);
		str_aux[1] = ft_str_toupper(split[j]);
		if (ft_strcmp(str_aux[0] + wild_in_start(split[i]), \
			str_aux[1] + wild_in_start(split[j])) > 0)
		{
			tmp = split[i];
			split[i] = split[j];
			split[j] = tmp;
		}
		str_free(str_aux[0]);
		str_free(str_aux[1]);
		j++;
	}
}

char	*sort_file_name(char *all_file_name, int i, int j)
{
	char	**split;

	split = ft_split(all_file_name, '\n');
	while (split[i])
	{
		j = i + 1;
		aux_sort_file_name(split, i, j);
		i++;
	}
	if (split[0])
		all_file_name = join_file_name(split, all_file_name);
	ft_free_str_vector(split);
	return (all_file_name);
}
