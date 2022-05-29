#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libohw/includes/libft.h"
#include "libohw/includes/ft_printf.h"

typedef struct global_set {
	volatile int	length;
	volatile int	state;
	char			*str;
	char				ch;
	int 			old;
	int				pid;
	int				k;
}global_set;