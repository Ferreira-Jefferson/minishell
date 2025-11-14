/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtertuli <jtertuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:59:11 by jtertuli          #+#    #+#             */
/*   Updated: 2025/11/14 08:59:50 by jtertuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

// load factor = num_elem / table size (256 = 0.39)
# define INITIAL_SIZE 256 

typedef enum e_env_type {
	ENV,
	EXPORT,
	SET
}	t_env_type;

typedef struct s_env_item {
	char				*key;
	char				*value;
	enum e_env_type		type;
	struct s_env_item	*next;
}	t_env_item;

typedef struct s_hash_table {
	int			size;
	t_env_item	**items;
}	t_hash_table;

unsigned long	hash_djb2(char *str);
t_hash_table	*ht_create(void);
void			ht_insert(t_hash_table *table, char *key, char *value, \
	t_env_type type);
char			*ht_search(t_hash_table *table, char *key);
void			ht_delete(t_hash_table *table, char *key);
void			ht_free_item(t_env_item *env_item);
void			ht_free(t_hash_table *table);
void			ht_print(t_hash_table *table);
void			ht_update_insert(t_hash_table *table, char *key, char *value, \
	t_env_type type);

#endif
