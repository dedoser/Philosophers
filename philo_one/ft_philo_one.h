/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_one.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:25:15 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 22:58:29 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_ONE_H
# define FT_PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num;
	int				philos_num;
	int				state;
	pthread_t		th;
	pthread_mutex_t	**mutex;
	int				sleep;
	int				eat;
	int				die;
	int				count;
	struct timeval	beg;
	size_t			last_m;
	int				start;
}	t_philo;

typedef struct s_t
{
	int					sleep;
	int					eat;
	int					die;
	int					count;
	int					num;
	t_philo				*mass;
	pthread_mutex_t		*mutex;
	int					death_num;
}	t_s;

int		ft_atoi(char *str);
size_t	get_time(t_philo *st);
int		init_time(t_philo *st);
int		start_philo(t_s *st);
int		ft_usleep(unsigned long long time);
void	alloc_check(void *ptr);
void	check_params(t_s *st);
void	*thread_start(void *arg);
#endif
