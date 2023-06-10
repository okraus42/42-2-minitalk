/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:36:31 by okraus            #+#    #+#             */
/*   Updated: 2023/06/10 18:50:58 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minitalk.h"

void	ft_confirm_msg(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Message received by the server.\n");
	else if (sig != SIGUSR2)
		ft_printf("ERROR: Caugh another signal = %d?!\n", sig);
}

void	ft_send_bit(int pid, unsigned char c)
{
	if (c)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(500);
}

// 00000001	=	1
// 00000010	=	2
// 00000100	=	4
// 00001000	=	8
// 00010000	=	16
// 00100000	=	32
// 01000000	=	64
// 10000000	=	128

void	ft_send_char(int pid, unsigned char c)
{
	ft_send_bit(pid, c & 1);
	ft_send_bit(pid, c & 2);
	ft_send_bit(pid, c & 4);
	ft_send_bit(pid, c & 8);
	ft_send_bit(pid, c & 16);
	ft_send_bit(pid, c & 32);
	ft_send_bit(pid, c & 64);
	ft_send_bit(pid, c & 128);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	pid;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		signal(SIGUSR1, ft_confirm_msg);
		while (argv[2][i])
		{
			ft_send_char(pid, argv[2][i]);
			i++;
		}
		ft_send_char(pid, '\n');
		ft_send_char(pid, 4);
	}
	else
	{
		ft_printf("FATAL ERROR\n");
		return (1);
	}
	return (0);
}
