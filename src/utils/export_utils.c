/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:14:59 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/15 10:24:29 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static char	*join_str_export(char **split, char *str_export_split)
{
	str_export_split = str_replace(str_export_split, "");
	while (*split)
	{
		str_export_split = str_cat(str_export_split, *split);
		str_export_split = str_cat(str_export_split, "\n");
		split++;
	}
	return (str_export_split);
}

static void	handle_sort_export(char	**split, int i, int j)
{
	char	*tmp;
	char	*str_aux[2];	

	while (split[i])
	{
		j = i + 1;
		while (split[j])
		{
			str_aux[0] = ft_str_toupper(split[i]);
			str_aux[1] = ft_str_toupper(split[j]);
			if (ft_strcmp(str_aux[0], str_aux[1]) > 0)
			{
				tmp = split[i];
				split[i] = split[j];
				split[j] = tmp;
			}
			str_free(str_aux[0]);
			str_free(str_aux[1]);
			j++;
		}
		i++;
	}
}

char	*sort_export(char *str_export)
{
	char	**split;

	split = ft_split(str_export, '\n');
	handle_sort_export(split, 0, 0);
	if (split[0])
		str_export = join_str_export(split, str_export);
	free_arr(split);
	return (str_export);
}

int	ft_isvalid_key(char *key)
{
	if (ft_strcmp(key, "_") == 0)
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}
