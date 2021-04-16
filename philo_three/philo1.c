/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:24:07 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/16 22:02:32 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

void	test(t_philo *st)
{
	sem_wait(st->sem);
	sem_wait(st->sem);
	printf("%ldms %d has taken a fork\n", get_time(st), st->num);
	printf("%ldms %d has taken a fork\n", get_time(st), st->num);
}

void	put_forks(t_philo *st)
{
	// pthread_mutex_lock(st->mutex);
	// pthread_mutex_unlock(st->mutex);
	printf("%ldms %d is sleeping\n", get_time(st), st->num);
	ft_usleep(st->sleep * 1000);
	printf("%ldms %d is thinking\n", get_time(st), st->num);
}

int		eat(t_philo *st)
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
	// st->last_m = get_time(st);
}

void	take_forks(t_philo *st)
{
	test(st);
}

void	*check_death(void *arg)
{
	t_philo	*st;

	st = (t_philo *)arg;
	while (1)
	{
		usleep(100);
		if (get_time(st) - st->last_m >= st->die)
		{
			printf("%ldms %d died\n", get_time(st),
				st->num);
			exit(0);
		}
	}
}

void	*philo_start(t_philo *st)
{
	pthread_create(&st->th, NULL, check_death, st);
	while (1)
	{
		take_forks(st);
		if (!eat(st))
			return (NULL);
		put_forks(st);
	}
}

int		check_philos(t_s *st)
{
	int	i;

	i = -1;
	while (++i < st->num)
		if (st->mass[i].state != -1)
			return (0);
	return (1);
}

void	init_sem(t_s *st)
{
	int	i;

	i = -1;
	while (++i < st->num)
	{
		st->mass[i].sem = st->sem;
		init_time(&st->mass[i]);
	}
}

void	fork_start(t_s *st)
{
	pid_t	t_pid;
	int		i;

	i = -1;
	while (++i < st->num)
	{
		t_pid = fork();
		if (t_pid == - 1)
		{
			printf("Fork error\n");
			exit(0);
		}
		else if (t_pid == 0)
			philo_start(&(st->mass[i]));
		else
			st->pid_mass[i] = t_pid;
	}
}

int		start_philo(t_s *st)
{
	int		i;
	int		status;

	i = -1;
	sem_unlink("semaphore");
	if ((st->sem = sem_open("semaphore", O_CREAT | S_IRWXU, 0644, st->num)) == SEM_FAILED)
	{
		return (0);
	}
	init_sem(st);
	fork_start(st);
	i = -1;
	while (++i < st->num)
	{
		waitpid(st->pid_mass[i], &status, WUNTRACED);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			return (0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			continue ;
	}
	return (0);
}
