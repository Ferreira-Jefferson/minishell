#include <unistd.h>
#include <signal.h>
#include <stdio.h>


static volatile sig_atomic_t g_signal_status = 0;

void handler(int signum)
{
	printf("Só entra no signal correto.\n");
	g_signal_status = signum;
	sleep(3);
}

int main(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);

	while(1)
	{
		printf("VAR: %d\n", g_signal_status);
		if (g_signal_status ==  SIGINT)
			g_signal_status = 0;
		sleep(1);
	}
	return (0);
}