/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fignigno <fignigno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:51:17 by fignigno          #+#    #+#             */
/*   Updated: 2021/02/16 09:57:49 by fignigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo_one.h"

int		ft_atoi(char *str)
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
