/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:36:48 by okraus            #+#    #+#             */
/*   Updated: 2023/05/14 15:10:20 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minitalk.h"

// 00000001	=	1
// 00000010	=	2
// 00000100	=	4
// 00001000	=	8
// 00010000	=	16
// 00100000	=	32
// 01000000	=	64
// 10000000	=	128

int	ft_handler3(int i)
{
	if (i == 0)
		return (1);
	if (i == 1)
		return (2);
	if (i == 2)
		return (4);
	if (i == 3)
		return (8);
	if (i == 4)
		return (16);
	if (i == 5)
		return (32);
	if (i == 6)
		return (64);
	return (128);
}

void	ft_handler(int sig)
{
	static unsigned char	c;
	static int				i;
	int						x;

	x = ft_handler3(i);
	if (sig == SIGUSR1)
		c += x;
	else if (sig == SIGUSR2)
		c += 0;
	else
		ft_printf("ERROR: Caugh another signal = %d?!\n", sig);
	i++;
	if (i == 8)
	{
		ft_printf("%c", c);
		c = 0;
		i = 0;
	}
}

//pid_t is integer

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("Server pid is: %i\n", pid);
	signal(SIGUSR1, ft_handler);
	signal(SIGUSR2, ft_handler);
	while (pid)
	{
		sleep(1);
	}
	ft_printf("FATAL ERROR\n");
	return (0);
}
