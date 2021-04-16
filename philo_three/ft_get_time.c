/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 02:25:47 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/15 21:36:20 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

int		ft_usleep(unsigned long long time)
{
	struct timeval	start;
	struct timeval	new;

	if (gettimeofday(&start, NULL) == -1)
		return (1);
	while (21)
	{
		usleep(21);
		if (gettimeofday(&new, NULL))
			return (1);
		if (((new.tv_sec - start.tv_sec) * 1000000 +
		new.tv_usec - start.tv_usec) > (long)time)
			break ;
	}
	return (0);
}

int		init_time(t_philo *st)
{
	return (gettimeofday(&st->beg, NULL));
}

size_t	get_time(t_philo *st)
{
	struct timeval	beg;
	int				sec;
	int				usec;

	if (gettimeofday(&beg, NULL))
		return (0);
	sec = beg.tv_sec - st->beg.tv_sec;
	usec = beg.tv_usec - st->beg.tv_usec;
	if (usec < 0)
	{
		sec--;
		usec += 1000000;
	}
	return (sec * 1000 + usec / 1000);
}
