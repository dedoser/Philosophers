/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:24:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/02/18 23:59:38 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

void	test(t_philo *st)
{
	pthread_mutex_lock(&(*st->mutex)[st->num - 1]);
	pthread_mutex_lock(&(*st->mutex)[st->num % st->philos_num]);
	st->state = EAT;
}

void	put_forks(t_philo *st)
{
	// pthread_mutex_lock(st->mutex);
	st->state = SLEEP;
	// pthread_mutex_unlock(st->mutex);
	printf("%ld, philo %d start sleeping\n", get_time(st), st->num);
	ft_usleep(st->sleep * 1000);
	printf("%ld, philo %d start thinking\n", get_time(st), st->num);
}

int		eat(t_philo *st)
{
	st->last_m = get_time(st);
	printf("%ld, philo %d start eating\n", st->last_m, st->num);
	ft_usleep(st->eat * 1000);
	pthread_mutex_unlock(&(*st->mutex)[st->num - 1]);
	pthread_mutex_unlock(&(*st->mutex)[st->num % st->philos_num]);
	st->count -= st->count != -1;
	if (st->count == 0)
	{
		printf("%ld, philo %d has done everything\n", get_time(st), st->num);
		st->state = -1;
		return (0);
	}
	return (1);
	// st->last_m = get_time(st);
}

void	take_forks(t_philo *st)
{
	st->state = HUNGRY;
	test(st);
	// while (st->state == HUNGRY)
	// {
	// 	pthread_mutex_lock(st->mutex);
	// 	test(st);
	// 	pthread_mutex_unlock(st->mutex);
	// }
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
	while (++i < st->num)
		pthread_mutex_init(&(st->mutex[i]), NULL);
	i = -1;
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
				printf("%ld, philo %d died(\n", get_time(&st->mass[i]), i + 1);
				// pthread_mutex_destroy(&st->mutex);
				return (0);
			}
		}
		i = -1;
		if (check_philos(st))
			return (0);
	}
	return (0);
}
