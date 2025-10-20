#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int i = 0;

	while (1)
	{
		sleep(1);
		printf("%d\n", i++);
	}
	// ctrl+c e ctrl+\ encerram o programa enquanto no shell o crtl+C fica printando o comando e ctrl+\ não faz nada
	return (0);
}