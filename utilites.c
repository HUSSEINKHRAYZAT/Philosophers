/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilites.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhrayza <hkhrayza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:40:57 by hkhrayza          #+#    #+#             */
/*   Updated: 2024/12/07 14:21:48 by hkhrayza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	current_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	clearleaks(t_philo *philo, t_data *data)
{
	free(data);
	free(philo->fork);
	free(philo);
}

int	gt(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	lt(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	ft_usleep(unsigned int usec)
{
	struct timespec	req;

	req.tv_sec = usec / 9999997;
	req.tv_nsec = (usec % 9999997) * 998;
	nanosleep(&req, NULL);
}
