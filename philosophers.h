/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 09:49:20 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/12/13 11:01:43 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <aio.h>
# include <pthread.h>
# include <stdbool.h>
# include <time.h>

# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0m\002"
# define GREEN "\001\033[1;32m\002"
# define RED "\001\033[1;31m\002"
# define BLUE "\001\033[1;34m\002"

typedef struct s_data
{
	int					philonum;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_think;
	int					nb_times_to_eat;

	uint64_t			startprocess;
	bool				all_has_ate;
	bool				any_died;
	pthread_mutex_t		mutexprint;
	pthread_mutex_t		mutexeat;
	pthread_mutex_t		mutex_all_eat;
	pthread_mutex_t		mutex_any_died;
}		t_data;

typedef struct s_philo
{
	int					id;
	uint64_t			lasteating;
	int					eatingcount;
	int					left_fork_id;
	int					right_fork_id;
	pthread_mutex_t		*fork;
	t_data				*data;
}	t_philo;

pthread_t	*create_philos(t_philo *philo, t_data *data);
void		clearleaks(t_philo *philo, t_data *data);
void		destroy_mutexes(t_philo *philo, t_data *data);
void		process(t_philo *philo, t_data *data);
void		end_eat(t_philo *self);
void		*philosopherfunction(void *arg);
void		philosopherdoing(t_philo *philo, char *inst);
void		someonedead(t_data *data);
void		everyoneeat(t_data *data);
int			philo_eats(t_philo *self);
int			checkdying(t_philo *philo);
int			check_all_ate(t_philo *philo);
int			create_philosphers(t_philo **philo, t_data *data);
int			create_mutexes(t_data **data);
int			variables(t_data **data, int argc, char **argv);
int			initializedata(t_philo **philo, t_data **data,
				int argc, char **argv);
int			isnum(char *str);
int			gt(int a, int b);
int			zeros(char **argv);
int			lt(int a, int b);
int			philosophers(t_philo *philo, t_data *data);
int			check_validation_args(char **argv);
long		current_time_in_ms(void);
bool		perform_eat_checks(t_philo *philo, t_data *data);
void		ft_usleep(unsigned int usec);
#endif