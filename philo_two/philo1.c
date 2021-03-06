/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:24:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/02/20 19:46:00 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

void	test(t_philo *st)
{
		sem_wait(*st->sem);
		sem_wait(*st->sem);
		printf("%ldms %d has taken a fork\n", st->last_m, st->num);
		printf("%ldms %d has taken a fork\n", st->last_m, st->num);
		st->state = EAT;
}

void	put_forks(t_philo *st)
{
	// pthread_mutex_lock(st->mutex);
	st->state = SLEEP;
	// pthread_mutex_unlock(st->mutex);
	printf("%ldms %d is sleeping\n", get_time(st), st->num);
	ft_usleep(st->sleep * 1000);
	printf("%ldms %d is thinking\n", get_time(st), st->num);
}

int		eat(t_philo *st)
{
	st->last_m = get_time(st);
	ft_usleep(st->eat * 1000);
	sem_post(*st->sem);
	sem_post(*st->sem);
	st->count -= st->count != -1;
	if (st->count == 0)
	{
		st->state = -1;
		return (0);
	}
	return (1);
	// st->last_m = get_time(st);
}

void	take_forks(t_philo *st)
{
	st->state = HUNGRY;
	while (st->state == HUNGRY)
		test(st);
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

int		check_philos(t_s *st)
{
	int	i;

	i = -1;
	while (++i < st->num)
		if (st->mass[i].state != -1)
			return (0);
	return (1);
}

int		start_philo(t_s *st)
{
	int		i;

	i = -1;
	sem_unlink("sem");
	if ((st->sem = sem_open("sem", O_CREAT | S_IRWXU, 0644, st->num)) == SEM_FAILED)
	{
		printf("%d\n", st->num);
		perror("sem_open");
		return (0);
	}
	int k;
	sem_getvalue(st->sem, &k);
	printf("%d\n", k);
	while (++i < st->num)
	{
		init_time(&st->mass[i]);
		pthread_create(&st->mass[i].th, NULL, thread_start, &st->mass[i]);
	}
	i = -1;
	while (1)
	{
		while (++i < st->num)
		{
			if (st->mass[i].count != 0 && get_time(&st->mass[i]) - st->mass[i].last_m >= st->die)
			{
				st->death_num = i + 1;
				sem_close(st->sem);
				return (0);
			}
		}
		i = -1;
		if (check_philos(st))
			return (0);
	}
	return (0);
}
