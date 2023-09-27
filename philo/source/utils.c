/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 15:26:39 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/27 20:13:52 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	accurate_usleep(uint64_t time, t_philo *philo)
{
	uint64_t	current;
	uint64_t	start;
	uint64_t	end;

	start = get_time_ms() * 1000;
	end = start + time;
	while (1)
	{
		if (check_death(philo->data) != 0)
			return ;
		current = get_time_ms() * 1000;
		if (current >= end)
			break ;
		else
			usleep(500);
	}
	return ;
}

uint64_t	get_time_ms(void)
{
	struct timeval	tv;
	uint64_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time);
}

void	lock_forks(t_philo *philo)
{
	if ((philo->philo_index + 1) % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	}
	if ((philo->philo_index + 1) % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	print_action(int index, char *action, t_data *data)
{
	uint64_t	time_now;

	time_now = get_time_ms() - data->start_time;
	if (check_death(data) == 0)
	{
		pthread_mutex_lock(&data->write);
		printf("%lld %d %s\n", time_now, index, action);
		pthread_mutex_unlock(&data->write);
	}
}
