/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_one.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:25:15 by fignigno          #+#    #+#             */
/*   Updated: 2021/02/20 19:35:37 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE
# define PHILO_ONE

# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define HUNGRY 0
# define EAT 1
# define SLEEP 2

typedef struct s_philo
{
	int				num;
	int				state;
	pthread_t		th;
	struct s_philo	*left;
	struct s_philo	*right;
	sem_t			**sem;
	int				sleep;
	int				eat;
	int				die;
	int				count;
	struct timeval	beg;
	size_t			last_m;
}	t_philo;

typedef struct s_t
{
	int					death_num;
	int					sleep;
	int					eat;
	unsigned long long	die;
	int					count;
	int					num;
	t_philo				*mass;
	sem_t				*sem;
}	t_s;

int		ft_atoi(char *str);
size_t	get_time(t_philo * st);
int		init_time(t_philo *st);
int		start_philo(t_s *st);
int		ft_usleep(unsigned long long time);

#endif
