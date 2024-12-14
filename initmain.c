/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:49:26 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/12/13 13:58:40 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	philo = NULL;
	if (argc == 5 || argc == 6)
	{
		if (zeros(argv))
			return (printf("You Enter invalid data\n"), 1);
		if (!check_validation_args(argv))
			return (printf("./philo NOPh die eat sleep [NB must eat]\n"), 1);
		if (!initializedata(&philo, &data, argc, argv))
			return (clearleaks(philo, data),
				printf("Something error happen during the process :( \n"), 1);
		if (philosophers(philo, data) != 0)
			return (clearleaks(philo, data), 1);
		clearleaks(philo, data);
	}
	else
	{
		printf("You must enter five Or six arguments\n");
		printf("All the arguments must be numbers\n");
	}
	return (0);
}

uint64_t	lasteatmut(t_philo *philo, t_data *data, int i, uint64_t eat)
{
	pthread_mutex_lock(&data->mutexeat);
	eat = philo[i].lasteating;
	pthread_mutex_unlock(&data->mutexeat);
	return (eat);
}

void	process(t_philo *philo, t_data *data)
{
	int			i;
	uint64_t	eat;
	char		*di;

	i = 0;
	di = " >>>>>>>>>>> Dead        <<<<<<<<<<<<<";
	while (1)
	{
		eat = lasteatmut(philo, data, i, eat);
		if (eat && perform_eat_checks(philo, data))
		{
			everyoneeat(data);
			printf(RED"EVERYONE EAT THE NUMBER OF MEALS THE USER ENTER\n"WHITE);
			break ;
		}
		if (eat && current_time_in_ms() - eat > (uint64_t)data->time_to_die)
		{
			someonedead(data);
			philosopherdoing(&philo[i], di);
			break ;
		}
		i = (i + 1) % data->philonum;
		ft_usleep(200);
	}
}

int	variables(t_data **data, int argc, char **argv)
{
	(*data)->startprocess = current_time_in_ms();
	(*data)->philonum = atoi(argv[1]);
	(*data)->time_to_die = atoi(argv[2]);
	(*data)->time_to_eat = atoi(argv[3]);
	(*data)->time_to_sleep = atoi(argv[4]);
	(*data)->time_to_think = 0;
	if (((*data)->philonum % 2)
		&& ((*data)->time_to_eat > (*data)->time_to_sleep))
		(*data)->time_to_think = 1 + ((*data)->time_to_eat
				- (*data)->time_to_sleep);
	if (argc == 5)
		(*data)->nb_times_to_eat = -1;
	if (argc == 6)
		(*data)->nb_times_to_eat = atoi(argv[5]);
	(*data)->all_has_ate = false;
	(*data)->any_died = false;
	if (create_mutexes(data))
		return (0);
	return (1);
}

int	initializedata(t_philo **philo, t_data **data, int argc, char **argv)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (*data == NULL)
		return (0);
	if (!variables(data, argc, argv))
		return (0);
	*philo = (t_philo *)malloc(sizeof(t_philo) * (size_t)(*data)->philonum);
	if (*philo == NULL)
		return (0);
	(*philo)->fork = NULL;
	if (!create_philosphers(philo, *data))
		return (0);
	return (1);
}
