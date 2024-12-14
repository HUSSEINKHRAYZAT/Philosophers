/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopherutilites.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:30:51 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/12/13 14:40:46 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_eats(t_philo *self)
{
	pthread_mutex_lock(&self->fork[lt(self->left_fork_id,
			self->right_fork_id)]);
	philosopherdoing(self, " >>>>>>>>>>> HANDEL FORK <<<<<<<<<<<<<");
	if (self->left_fork_id == self->right_fork_id)
	{
		pthread_mutex_unlock(&self->fork[lt(self->left_fork_id,
				self->right_fork_id)]);
		return (1);
	}
	pthread_mutex_lock(&self->fork[gt(self->left_fork_id,
			self->right_fork_id)]);
	philosopherdoing(self, " >>>>>>>>>>> HANDEL FORK <<<<<<<<<<<<<");
	philosopherdoing(self, " >>>>>>>>>>> EATING      <<<<<<<<<<<<<");
	pthread_mutex_lock(&self->data->mutexeat);
	self->lasteating = current_time_in_ms();
	self->eatingcount++;
	pthread_mutex_unlock(&self->data->mutexeat);
	if (check_all_ate(self))
	{
		end_eat (self);
		return (1);
	}
	ft_usleep(self->data->time_to_eat * 1000);
	end_eat (self);
	return (0);
}

void	*philosopherfunction(void *arg)
{
	t_philo	*self;

	self = (t_philo *) arg;
	if (self->id % 2 == 0)
	{
		philosopherdoing(self, " >>>>>>>>>>> THINKING    <<<<<<<<<<<<<");
		ft_usleep(self->data->time_to_eat * 1000);
	}
	while (1)
	{
		if (checkdying(self))
			break ;
		if (philo_eats (self) != 0)
			break ;
		philosopherdoing(self, " >>>>>>>>>>> THINKING    <<<<<<<<<<<<<");
		ft_usleep(self->data->time_to_think * 1000);
	}
	return (NULL);
}

bool	perform_eat_checks(t_philo *philo, t_data *data)
{
	int	i;
	int	done;
	int	meals_count;

	if (data->nb_times_to_eat == -1)
		return (false);
	i = -1;
	done = -1;
	while (++i < data->philonum)
	{
		pthread_mutex_lock(&philo->data->mutexeat);
		meals_count = philo[i].eatingcount;
		pthread_mutex_unlock(&philo->data->mutexeat);
		if (meals_count >= data->nb_times_to_eat)
			if (++done == data->philonum - 1)
				return (true);
		ft_usleep (50);
	}
	return (false);
}

void	philosopherdoing(t_philo *philo, char *inst)
{
	char	*comp;

	comp = " >>>>>>>>>>> Dead        <<<<<<<<<<<<<";
	pthread_mutex_lock(&philo->data->mutexprint);
	if (strcmp(inst, comp) == 0 || (!checkdying(philo)
			&& !check_all_ate(philo)))
	{
		printf(RED"%lu "BLUE"%d"GREEN"%s\n"WHITE,
			current_time_in_ms() - philo->data->startprocess, philo->id, inst);
	}
	pthread_mutex_unlock(&philo->data->mutexprint);
}

int	create_philosphers(t_philo **philo, t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc (sizeof(pthread_mutex_t) * ((size_t)data->philonum));
	if (fork == NULL)
		return (0);
	i = 0;
	while (i < data->philonum)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < data->philonum)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].lasteating = data->startprocess;
		(*philo)[i].eatingcount = 0;
		(*philo)[i].left_fork_id = i;
		(*philo)[i].right_fork_id = (i + 1) % data->philonum;
		(*philo)[i].fork = fork;
		(*philo)[i].data = data;
		i++;
	}
	return (1);
}
