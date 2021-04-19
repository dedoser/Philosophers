/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:21:56 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 23:07:21 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_two.h"

void	init_philo(t_s *st)
{
	int	i;

	i = -1;
	st->death_num = -1;
	while (++i < st->num)
	{
		memset(&st->mass[i], 0, sizeof(t_philo));
		st->mass[i].sem = st->sem;
		st->mass[i].sleep = st->sleep;
		st->mass[i].die = st->die;
		st->mass[i].eat = st->eat;
		st->mass[i].count = st->count;
		st->mass[i].num = i + 1;
	}
}

void	finish_work(t_s *st)
{
	int	i;

	i = -1;
	while (++i < st->num)
		pthread_detach(st->mass[i].th);
	free(st->mass);
}

int	philo(char **argv)
{
	t_s	st;

	sem_unlink("semaphore");
	st.num = ft_atoi(argv[1]);
	st.die = ft_atoi(argv[2]);
	st.eat = ft_atoi(argv[3]);
	st.sleep = ft_atoi(argv[4]);
	st.count = ft_atoi(argv[5]);
	st.mass = (t_philo *)malloc(sizeof(t_philo) * st.num);
	alloc_check(st.mass);
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
