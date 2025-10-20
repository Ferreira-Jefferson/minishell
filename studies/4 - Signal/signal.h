#ifndef SIGNAL_H
# define SIGNAL_H

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>

int get_g_signal_status(void);
void reset_g_signal_status();

int setup_signals(void);

#endif