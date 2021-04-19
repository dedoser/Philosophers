/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_three.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:25:15 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 22:59:53 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_THREE_H
# define FT_PHILO_THREE_H

# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int				num;
	int				state;
	sem_t			*sem;
	int				sleep;
	int				eat;
	int				die;
	int				count;
	pthread_t		th;
	struct timeval	beg;
	size_t			last_m;
}	t_philo;

typedef struct s_t
{
	int					death_num;
	int					sleep;
	int					eat;
	int					die;
	int					count;
	int					num;
	t_philo				*mass;
	sem_t				*sem;
	pid_t				*pid_mass;
}	t_s;

int		ft_atoi(char *str);
size_t	get_time(t_philo *st);
int		init_time(t_philo *st);
int		start_philo(t_s *st);
int		ft_usleep(unsigned long long time);
void	check_params(t_s *st);
void	alloc_check(void *ptr);
void	philo_start(t_philo *st);
#endif
