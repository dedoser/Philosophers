/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 22:03:37 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 22:58:57 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

static int	check_philos(t_s *st)
{
	int	i;

	i = -1;
	while (++i < st->num)
		if (st->mass[i].state != -1)
			return (0);
	return (1);
}

int	start_philo(t_s *st)
{
	int		i;

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
			if (st->mass[i].count != 0
				&& get_time(&st->mass[i]) - st->mass[i].last_m >= (size_t)st->die)
			{
				st->death_num = i + 1;
				return (0);
			}
		}
		i = -1;
		if (check_philos(st))
			return (0);
	}
	return (0);
}
