/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:20:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/07/19 13:56:35 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
		exit(0);
}

static int	send_bit(pid_t pid, int bit)
{
	int	sig;
	int	res;

	sig = SIGUSR1;
	if (bit)
		sig = SIGUSR2;
	g_ack = 0;
	res = kill(pid, sig);
	if (res == -1)
		return (1);
	while (!g_ack)
		usleep(100);
	return (0);
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
	pid_t				pid;
	char				*str;
	struct sigaction	sa;

	if (argc != 3)
		return (1);
	pid = (pid_t)ft_atoi(argv[1]);
	str = argv[2];
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
	return (0);
}
