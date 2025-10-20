#include "minishell.h"

static volatile sig_atomic_t	g_signal_status;

int	get_g_signal_status(void)
{
	return (g_signal_status);
}

void	reset_g_signal_status(void)
{
	g_signal_status = 0;
}

void	handler(int signum)
{
	g_signal_status = signum;
}

int	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_stp;

	g_signal_status = 0;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_int.sa_handler = &handler;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
	sigemptyset(&sa_stp.sa_mask);
	sa_stp.sa_flags = 0;
	sa_stp.sa_handler = SIG_IGN;
	sigaction(SIGTSTP, &sa_stp, NULL);
	return (0);
}
