/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:21:56 by fignigno          #+#    #+#             */
/*   Updated: 2021/02/20 19:33:37 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

void	init_philo(t_s *st)
{
	int	i;
	int	l;
	int	r;

	i = -1;
	st->death_num = -1;
	while (++i < st->num)
	{
		memset(&st->mass[i], 0, sizeof(t_philo));
		l = i % st->num - 1;
		r = i % st->num + 1;
		st->mass[i].left = l < 0 ? &st->mass[st->num - 1] : &st->mass[l];
		st->mass[i].right = r == st->num ? &st->mass[0] : &st->mass[r];
		st->mass[i].sem = &st->sem;
		st->mass[i].sleep = st->sleep;
		st->mass[i].die = st->die;
		st->mass[i].eat = st->eat;
		st->mass[i].count = st->count;
		st->mass[i].num = i + 1;
		st->mass[i].state = HUNGRY;
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

int		philo(char **argv)
{
	t_s st;

	if ((st.num = ft_atoi(argv[1])) < 0 || (st.die = ft_atoi(argv[2])) < 0 ||
		(st.eat = ft_atoi(argv[3])) < 0 || (st.sleep = ft_atoi(argv[4])) < 0)
	{
		printf("Not valid arguments\n");
		return (-1);
	}
	if ((st.count = ft_atoi(argv[5])) == -2)
	{
		printf("Not valid arguments\n");
		return (-1);
	}
	if (!(st.mass = (t_philo *)malloc(sizeof(t_philo) * st.num)))
	{
		printf("Malloc error\n");
		return (-1);
	}
	init_philo(&st);
	start_philo(&st);
	if (st.death_num > 0)
		printf("%ldms %d died\n", get_time(&st.mass[st.death_num - 1]),
		st.death_num);
	finish_work(&st);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		return (philo(argv));
	else
		printf("Wrong number of arguments\n");
	return (0);
}
