/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 22:54:30 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 22:56:04 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_three.h"

static void	init_sem(t_s *st)
{
	int	i;

	i = -1;
	while (++i < st->num)
	{
		st->mass[i].sem = st->sem;
		init_time(&st->mass[i]);
	}
}

static void	fork_start(t_s *st)
{
	pid_t	t_pid;
	int		i;

	i = -1;
	while (++i < st->num)
	{
		t_pid = fork();
		if (t_pid == -1)
		{
			printf("Fork error\n");
			exit(0);
		}
		else if (t_pid == 0)
			philo_start(&(st->mass[i]));
		else
			st->pid_mass[i] = t_pid;
	}
}

int	start_philo(t_s *st)
{
	int		i;
	int		status;

	i = -1;
	sem_unlink("semaphore");
	st->sem = sem_open("semaphore", O_CREAT | S_IRWXU, 0644, st->num);
	if (st->sem == SEM_FAILED)
		return (0);
	init_sem(st);
	fork_start(st);
	i = -1;
	while (++i < st->num)
	{
		waitpid(st->pid_mass[i], &status, WUNTRACED);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			return (0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			continue ;
	}
	return (0);
}
