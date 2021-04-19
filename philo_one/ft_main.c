/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:21:56 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 22:04:55 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

static int	add_malloc(t_s *st)
{
	st->mass = (t_philo *)malloc(sizeof(t_philo) * st->num);
	st->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * st->num);
	alloc_check(st->mutex);
	alloc_check(st->mass);
	return (0);
}

static void	init_philo(t_s *st)
{
	int	i;

	i = -1;
	st->death_num = -1;
	while (++i < st->num)
	{
		memset(&st->mass[i], 0, sizeof(t_philo));
		st->mass[i].mutex = &st->mutex;
		st->mass[i].sleep = st->sleep;
		st->mass[i].die = st->die;
		st->mass[i].eat = st->eat;
		st->mass[i].count = st->count;
		st->mass[i].num = i + 1;
		st->mass[i].philos_num = st->num;
		st->mass[i].start = st->mass[i].num % 2;
	}
	i = -1;
	while (++i < st->num)
		pthread_mutex_init(&(st->mutex[i]), NULL);
}

static void	finish_work(t_s *st)
{
	int	i;

	i = -1;
	while (++i < st->num)
		pthread_detach(st->mass[i].th);
	i = -1;
	while (++i < st->num)
		pthread_mutex_destroy(&st->mutex[i]);
}

static int	philo(char **argv)
{
	t_s	st;

	st.num = ft_atoi(argv[1]);
	st.die = ft_atoi(argv[2]);
	st.eat = ft_atoi(argv[3]);
	st.sleep = ft_atoi(argv[4]);
	st.count = ft_atoi(argv[5]);
	check_params(&st);
	if (add_malloc(&st))
		return (0);
	init_philo(&st);
	start_philo(&st);
	if (st.death_num > 0)
		printf("%ldms %d died\n", get_time(&st.mass[st.death_num - 1]),
			st.death_num);
	finish_work(&st);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		return (philo(argv));
	else
		printf("Wrong number of arguments\n");
	return (0);
}
