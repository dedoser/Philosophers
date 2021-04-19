/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 23:09:51 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 23:14:18 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_two.h"

int	check_philos(t_s *st)
{
	int	i;

	i = -1;
	while (++i < st->num)
		if (st->mass[i].state != -1)
			return (0);
	return (1);
}

int	main_thread(t_s *st)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < st->num)
		{
			if (st->mass[i].count != 0
				&& get_time(&st->mass[i]) - st->mass[i].last_m >= (size_t)st->die)
			{
				st->death_num = i + 1;
				return (0);
			}
		}
		if (check_philos(st))
			return (0);
	}
	return (0);
}
