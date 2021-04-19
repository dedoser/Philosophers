/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:24:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 23:13:17 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_two.h"

void	put_forks(t_philo *st)
{
	printf("%ldms %d is sleeping\n", get_time(st), st->num);
	ft_usleep(st->sleep * 1000);
	printf("%ldms %d is thinking\n", get_time(st), st->num);
}

int	eat(t_philo *st)
{
	st->last_m = get_time(st);
	printf("%ldms %d is eating\n", st->last_m, st->num);
	ft_usleep(st->eat * 1000);
	sem_post(st->sem);
	sem_post(st->sem);
	st->count -= st->count != -1;
	if (st->count == 0)
	{
		st->state = -1;
		return (0);
	}
	return (1);
}

void	take_forks(t_philo *st)
{
	sem_wait(st->sem);
	sem_wait(st->sem);
	printf("%ldms %d has taken a fork\n", get_time(st), st->num);
	printf("%ldms %d has taken a fork\n", get_time(st), st->num);
}

void	*thread_start(void *arg)
{
	t_philo	*st;

	st = (t_philo *)arg;
	while (1)
	{
		take_forks(st);
		if (!eat(st))
			return (NULL);
		put_forks(st);
	}
}

int	start_philo(t_s *st)
{
	int		i;

	i = -1;
	sem_unlink("semaphore");
	st->sem = sem_open("semaphore", O_CREAT | S_IRWXU, 0644, st->num);
	if (st->sem == SEM_FAILED)
	{
		printf("%d\n", st->num);
		perror("sem_open");
		return (0);
	}
	while (++i < st->num)
		st->mass[i].sem = st->sem;
	i = -1;
	while (++i < st->num)
	{
		init_time(&st->mass[i]);
		pthread_create(&st->mass[i].th, NULL, thread_start, &st->mass[i]);
	}
	return (main_thread(st));
}
