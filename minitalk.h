/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:43:03 by hoh               #+#    #+#             */
/*   Updated: 2022/05/31 17:43:43 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include "libohw/includes/libft.h"
# include "libohw/includes/ft_printf.h"

typedef struct s_global_set {
	volatile int			length;
	volatile sig_atomic_t	state;
	volatile sig_atomic_t	ch;
	char					*str;
	int						old;
	int						pid;
	int						k;
	int						erno;
}t_global_set;

#endif
