#ifndef STRUCTS_H
# define STRUCTS_H

#define INITIAL_SIZE 256 // load factor = num_elem / table size (256 = 0.39)

typedef struct s_env_item {
	char				*key;
	char				*value;
	struct s_env_item	*next; // Separate Chaining
} t_env_item;

typedef struct s_hash_table {
	int			size;
	t_env_item	**items;
} t_hash_table;

unsigned long	hash_djb2(char *str);
t_hash_table	*ht_create(void);
void			ht_insert(t_hash_table *table, char *key, char *value);
#endif