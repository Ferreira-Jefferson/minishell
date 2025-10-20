#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

int		get_g_signal_status(void);
void	reset_g_signal_status(void);
int		setup_signals(void);

#endif