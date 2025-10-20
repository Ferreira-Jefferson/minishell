#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
	printf("sig: %d\n", signum);
}

int main()
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
	while(1)
	{
		sleep(1);
	}
	return 0;
}