/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:41:18 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/12/13 10:16:22 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutexes(t_data **data)
{
	pthread_mutex_init((&(*data)->mutexeat), NULL);
	pthread_mutex_init((&(*data)->mutex_all_eat), NULL);
	pthread_mutex_init((&(*data)->mutex_any_died), NULL);
	pthread_mutex_init((&(*data)->mutexprint), NULL);
	return (0);
}

void	destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->philonum)
		pthread_mutex_destroy(&philo->fork[i++]);
	i = 0;
	pthread_mutex_destroy(&data->mutex_all_eat);
	pthread_mutex_destroy(&data->mutexeat);
	pthread_mutex_destroy(&data->mutex_any_died);
	pthread_mutex_destroy(&data->mutexprint);
}

void	someonedead(t_data *data)
{
	pthread_mutex_lock(&data->mutex_any_died);
	data->any_died = true;
	pthread_mutex_unlock(&data->mutex_any_died);
}

void	everyoneeat(t_data *data)
{
	pthread_mutex_lock(&data->mutex_all_eat);
	data->all_has_ate = true;
	pthread_mutex_unlock(&data->mutex_all_eat);
}

int	checkdying(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_any_died);
	if (philo->data->any_died)
	{
		pthread_mutex_unlock(&philo->data->mutex_any_died);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->mutex_any_died);
	return (false);
}
