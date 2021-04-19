/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:21:56 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 22:59:38 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_three.h"

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
		kill(st->pid_mass[i], SIGKILL);
	free(st->mass);
	free(st->pid_mass);
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
	st.pid_mass = (pid_t *)malloc(sizeof(pid_t) * st.num);
	alloc_check(st.mass);
	alloc_check(st.pid_mass);
	init_philo(&st);
	start_philo(&st);
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
