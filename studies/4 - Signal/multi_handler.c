#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
	printf("sig: %d\n", signum);
}

int main()
{
	struct sigaction sa_int;
	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGQUIT);
	sa_int.sa_handler = handler; 
	sigaction(SIGINT, &sa_int, NULL);
	
	struct sigaction sa_quit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
	while(1)
		sleep(1);
	return 0;
}