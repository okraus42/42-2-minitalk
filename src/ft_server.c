/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:36:48 by okraus            #+#    #+#             */
/*   Updated: 2023/06/15 17:17:52 by okraus           ###   ########.fr       */
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

char	*g_s;

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

void	ft_handler2(siginfo_t *info, unsigned char c)
{
	char	s[2];

	s[0] = c;
	s[1] = 0;
	if (c != 4)
	{
		if (g_s)
		{
			g_s = ft_strjoin_freeleft(g_s, s);
		}
		else
		{
			g_s = malloc(sizeof(char) * 2);
			g_s[0] = c;
			g_s[1] = 0;
		}
		kill(info->si_pid, SIGUSR2);
	}
	else
	{
		ft_printf("%s", g_s);
		kill(info->si_pid, SIGUSR1);
		free(g_s);
		g_s = NULL;
	}
}

void	ft_handler(int sig, siginfo_t *info, void *s)
{
	static unsigned char	c;
	static int				i;
	int						x;

	(void)s;
	x = ft_handler3(i);
	if (sig == SIGUSR1)
		c += x;
	else if (sig == SIGUSR2)
		c += 0;
	else
		ft_printf_fd(2, "ERROR: Caugh another signal = %d?!\n", sig);
	i++;
	if (i == 8)
	{
		ft_handler2(info, c);
		c = 0;
		i = 0;
	}
	else
		kill(info->si_pid, SIGUSR2);
	usleep(5);
}

//pid_t is integer

int	main(void)
{
	pid_t				pid;
	struct sigaction	sigact;

	g_s = NULL;
	pid = getpid();
	ft_printf("Server pid is: %4C%i%0C\n", pid);
	sigact.sa_sigaction = ft_handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (pid)
	{
		sleep(5);
	}
	ft_printf("FATAL ERROR\n");
	return (0);
}
