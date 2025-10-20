#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler_SIGINT(int signum)
{
	printf("sigint: %d\n", signum);
	sleep(3);
}

void handler_SIGQUIT(int signum)
{
	printf("sigquit: %d\n", signum);
}


int main()
{
	struct sigaction sa_int;
	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGQUIT);
	sa_int.sa_handler = handler_SIGINT;	
	sigaction(SIGINT, &sa_int, NULL);

	struct sigaction sa_quit;
	sigemptyset(&sa_quit.sa_mask);
	sigaddset(&sa_quit.sa_mask, SIGINT);
	sa_quit.sa_handler = handler_SIGQUIT;	
	sigaction(SIGQUIT, &sa_quit, NULL);
	while(1)
		sleep(1);
	return 0;
}