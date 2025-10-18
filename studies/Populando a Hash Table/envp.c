#include <stdio.h>
#include <stdlib.h>

void fake_split(char *value)
{
	int key = 0;

	if (*value)
		printf("key: ");
	while (*value)
	{
		if (*value == '=')
			printf(" | value: ");
		else
			printf("%c", *value);
		value++;
	}
	printf("\n");
}

int main(int argc, char *argv[], char **envp)
{
	char **item;

	while (*envp)
	{
		fake_split(*envp);
		envp++;
	}
	return (0);
}