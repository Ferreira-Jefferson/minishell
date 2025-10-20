#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
	printf("sig: %d\n", signum);
}

int main()
{
	while(1)
	{
		sleep(1);
		signal(SIGINT, handler);
	}
	return 0;
}