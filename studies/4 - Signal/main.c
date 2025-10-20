
#include "signal.h"

int ft_event_hook(void)
{
	if (get_g_signal_status() != 0)
	{
		write(1, "^C", 2);
		rl_done = 1;
		reset_g_signal_status(); 
	}
	return (0);
}
int main()
{
	char *input;
	rl_catch_signals = 0;
	rl_event_hook = ft_event_hook;

	setup_signals();
	while (1)
	{
		input = readline("teste> ");
		if (!input && get_g_signal_status() == 0)
		{
			write(1, "exit\n", 5);
			break ;
		}
		free(input);
	}
	return (0);
}