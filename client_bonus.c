/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:46:30 by ayusa             #+#    #+#             */
/*   Updated: 2025/07/16 20:36:13 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_ack = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
	{
		write(1, "Message sent successfully!\n", 28);
		exit(0);
	}
}

static void	send_bit(pid_t pid, int bit)
{
	int	sig;

	sig = SIGUSR1;
	if (bit)
		sig = SIGUSR2;
	g_ack = 0;
	kill(pid, sig);
	while (!g_ack)
		usleep(50);
}

static void	send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_bit(pid, (c >> i) & 1);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*str;

	if (argc != 3)
		return (1);
	pid = (pid_t)ft_atoi(argv[1]);
	str = argv[2];
	signal(SIGUSR1, ack_handler);
	signal(SIGUSR2, ack_handler);
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
	return (0);
}
