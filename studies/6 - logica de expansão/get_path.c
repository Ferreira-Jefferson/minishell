#include <stdio.h>
#include <string.h>

struct env {
	char *key;
	char *value;
} ;

struct group
{
	struct env table[3];
	char *str;
};


void expander(struct group *value)
{
	int len_total = strlen(value->str);
	int len_total_percorrido = 0;

	
}
int main(void)
{
	struct env hash[3] = { {"key_1", "value_1"}, {"key_2", "value_2"},  {"key_3", "value_3"}};
	printf("[0]: {%s: %s}\n", hash[0].key, hash[0].value);
	printf("[1]: {%s: %s}\n", hash[1].key, hash[1].value);
	printf("[2]: {%s: %s}\n", hash[2].key, hash[2].value);
	printf("cmp: %d %d\n", strcmp(hash[0].key, hash[1].key), strcmp(hash[0].key, "key_1"));
	char str_teste[45] = "olá $key_1, tudo bem no $key_2 e na $key_3?";

	struct group val_group = { *hash};
	val_group.str = strdup(str_teste);
	printf("[0]: {%s: %s}\n", val_group.table[0].key, val_group.table[0].value);
	printf("teste: [%s]\n", val_group.str);
}