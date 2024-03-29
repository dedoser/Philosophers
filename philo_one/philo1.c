/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:24:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 22:04:38 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

static void	test(t_philo *st)
{
	if (st->start)
	{
		st->start--;
		ft_usleep(2);
	}
	pthread_mutex_lock(&(*st->mutex)[st->num - 1]);
	pthread_mutex_lock(&(*st->mutex)[st->num % st->philos_num]);
	printf("%ldms %d has taken fork\n", get_time(st), st->num);
	printf("%ldms %d has taken fork\n", get_time(st), st->num);
}

static void	put_forks(t_philo *st)
{
	printf("%ldms %d is sleeping\n", get_time(st), st->num);
	ft_usleep(st->sleep * 1000);
	printf("%ldms %d is thinking\n", get_time(st), st->num);
}

static int	eat(t_philo *st)
{
	st->last_m = get_time(st);
	printf("%ldms %d is eating\n", st->last_m, st->num);
	ft_usleep(st->eat * 1000);
	pthread_mutex_unlock(&(*st->mutex)[st->num - 1]);
	pthread_mutex_unlock(&(*st->mutex)[st->num % st->philos_num]);
	st->count -= st->count != -1;
	if (st->count == 0)
	{
		st->state = -1;
		return (0);
	}
	return (1);
}

static void	take_forks(t_philo *st)
{
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
