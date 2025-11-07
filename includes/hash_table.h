#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define INITIAL_SIZE 256 // load factor = num_elem / table size (256 = 0.39)

typedef enum e_env_type {
	ENV,
	EXPORT,
	SET
}	t_env_type;

typedef struct s_env_item {
	char				*key;
	char				*value;
	enum e_env_type		type;
	struct s_env_item	*next; // Separate Chaining
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
void 			ht_update_insert(t_hash_table *table, char *key, char *value, \
	t_env_type type);

#endif