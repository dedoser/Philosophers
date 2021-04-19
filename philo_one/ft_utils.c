/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:51:17 by fignigno          #+#    #+#             */
/*   Updated: 2021/04/19 22:05:43 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

int	ft_atoi(char *str)
{
	int	res;
	int	i;

	if (!str)
		return (-1);
	i = -1;
	res = 0;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-2);
		res = res * 10 + str[i] - '0';
	}
	return (res);
}

void	alloc_check(void *ptr)
{
	if (ptr)
		return ;
	printf("Malloc error\n");
	exit(0);
}

void	check_params(t_s *st)
{
	if (st->die < 0 || st->eat < 0 || st->num < 0 || st->sleep < 0
		|| st->count == -2)
	{
		printf("Not valid arguments\n");
		exit (0);
	}
}
