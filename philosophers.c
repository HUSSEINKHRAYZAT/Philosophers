/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:45:22 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/12/13 10:16:32 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t	*create_philos(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * (size_t)data->philonum);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < data->philonum)
	{
		if (pthread_create(&threads[i], 0,
				philosopherfunction, (void *)&philo[i]))
		{
			while (i--)
				pthread_join(threads[i], NULL);
			free(threads);
			return (NULL);
		}
		i++;
	}
	return (threads);
}

int	philosophers(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	*threads;

	threads = create_philos(philo, data);
	if (!threads)
		return (1);
	process(philo, data);
	i = 0;
	while (i < data->philonum)
	{
		if (pthread_join(threads[i], NULL))
			return (1);
		i++;
	}
	destroy_mutexes(philo, data);
	free(threads);
	return (0);
}

void	end_eat(t_philo *self)
{
	philosopherdoing(self, " >>>>>>>>>>> SLEEPING    <<<<<<<<<<<<<");
	pthread_mutex_unlock(
		&self->fork[gt(self->left_fork_id, self->right_fork_id)]);
	pthread_mutex_unlock(
		&self->fork[lt(self->left_fork_id, self->right_fork_id)]);
	ft_usleep(self->data->time_to_sleep * 1000);
}
