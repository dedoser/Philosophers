/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:24:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 23:00:34 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_three.h"

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
		exit(1);
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

void	*check_death(void *arg)
{
	t_philo	*st;

	st = (t_philo *)arg;
	while (1)
	{
		usleep(100);
		if (get_time(st) - st->last_m >= (size_t)st->die)
		{
			printf("%ldms %d died\n", get_time(st),
				st->num);
			exit(0);
		}
	}
}

void	philo_start(t_philo *st)
{
	pthread_create(&st->th, NULL, check_death, st);
	while (1)
	{
		take_forks(st);
		if (!eat(st))
			return ;
		put_forks(st);
	}
}
