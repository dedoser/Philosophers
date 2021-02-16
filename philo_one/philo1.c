/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:24:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/02/16 19:14:17 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

void	test(t_philo *st)
{
	if (st->state == HUNGRY && st->left->state != EAT
		&& st->right->state != EAT)
	{
		st->state = EAT;
	}
}

void	put_forks(t_philo *st)
{
	pthread_mutex_lock(st->mutex);
	st->state = SLEEP;
	test(st->left);
	test(st->right);
	pthread_mutex_unlock(st->mutex);
	printf("%ld, philo %d start sleeping\n", get_time(st), st->num);
	ft_usleep(st->sleep * 1000);
	printf("%ld, philo %d start thinking\n", get_time(st), st->num);
}

void	eat(t_philo *st)
{
	st->last_m = get_time(st);
	printf("%ld, philo %d start eating\n", st->last_m, st->num);
	ft_usleep(st->eat * 1000);
	// st->last_m = get_time(st);
}

void	take_forks(t_philo *st)
{
	st->state = HUNGRY;
	while (st->state == HUNGRY)
	{
		pthread_mutex_lock(st->mutex);
		test(st);
		pthread_mutex_unlock(st->mutex);
	}
}

void	*thread_start(void *arg)
{
	t_philo	*st;

	st = (t_philo *)arg;
	while (1)
	{
		take_forks(st);
		eat(st);
		put_forks(st);
	}
}

int		start_philo(t_s *st)
{
	int		i;

	i = -1;
	pthread_mutex_init(&st->mutex, NULL);
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
			if (get_time(&st->mass[i]) - st->mass[i].last_m > st->die)
			{
				printf("%ld, philo %d died(\n", get_time(&st->mass[i]), i + 1);
				exit(0);
			}
		}
		i = -1;
	}
	return (0);
}
