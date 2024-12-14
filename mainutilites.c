/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainutilites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:50:16 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/12/13 13:29:08 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_validation_args(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!isnum(argv[i]))
			return (printf("The input arguments is not valid\n"), 0);
		i++;
	}
	return (1);
}

int	zeros(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '0' || argv[i][0] == '-' || argv[i][0] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	check_all_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_all_eat);
	if (philo->data->all_has_ate)
	{
		pthread_mutex_unlock(&philo->data->mutex_all_eat);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->mutex_all_eat);
	return (false);
}
