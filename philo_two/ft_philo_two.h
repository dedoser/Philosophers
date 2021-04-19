/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_two.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:25:15 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 23:14:06 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_TWO_H
# define FT_PHILO_TWO_H

# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num;
	int				state;
	pthread_t		th;
	struct s_philo	*left;
	struct s_philo	*right;
	sem_t			*sem;
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
	int					die;
	int					count;
	int					num;
	t_philo				*mass;
	sem_t				*sem;
}	t_s;

int		ft_atoi(char *str);
size_t	get_time(t_philo *st);
int		init_time(t_philo *st);
int		start_philo(t_s *st);
int		ft_usleep(unsigned long long time);
void	check_params(t_s *st);
void	alloc_check(void *ptr);
int		main_thread(t_s *st);
#endif
