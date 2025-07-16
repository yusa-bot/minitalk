/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayusa <ayusa@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:20:55 by ayusa             #+#    #+#             */
/*   Updated: 2025/07/16 20:46:18 by ayusa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_bit(pid_t pid, int bit)
{
	int	sig;

	sig = SIGUSR1;
	if (bit)
		sig = SIGUSR2;
	kill(pid, sig);
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
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
	return (0);
}
