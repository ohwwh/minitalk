#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "libohw/includes/libft.h"
#include "libohw/includes/ft_printf.h"

typedef struct global_set {
	volatile int			length;
	volatile sig_atomic_t	state;
	volatile sig_atomic_t	ch;
	char					*str;
	int 					old;
	int						pid;
	int						k;
	int						oldch;
	int						erno;
}global_set;