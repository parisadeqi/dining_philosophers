/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checker.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 15:28:53 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/27 20:11:10 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	pthread_mutex_lock(&data->death);
	if (data->dead_philo == true)
	{
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->death);
	return (0);
}

int	eating_times_check(t_data *data, int i)
{
	if (data->count_must_eat != 0)
	{
		pthread_mutex_lock(&data->philo_struct[i].time_lock);
		if (data->philo_struct[i].eating_times > data->count_must_eat)
		{
			pthread_mutex_unlock(&data->philo_struct[i].time_lock);
			return (0);
		}
		else
		{
			pthread_mutex_unlock(&data->philo_struct[i].time_lock);
			i++;
		}
	}
	else
		i++;
	return (i);
}

void	death_announcement(t_data *data, int i)
{
	uint64_t	time_now;

	pthread_mutex_lock(&data->write);
	pthread_mutex_lock(&data->death);
	data->dead_philo = true;
	time_now = get_time_ms() - data->start_time;
	printf("%lu %d %s\n", time_now, i + 1, "is dead");
	pthread_mutex_unlock(&data->death);
	pthread_mutex_unlock(&data->write);
}

int	supervisor(t_data *data, int i)
{
	uint64_t	time_now;
	uint64_t	time_after_eat;
	int			res;

	pthread_mutex_lock(&data->philo_struct[i].time_lock);
	time_now = get_time_ms() - data->start_time;
	time_after_eat = time_now - data->philo_struct[i].last_time_eat;
	pthread_mutex_unlock(&data->philo_struct[i].time_lock);
	if (time_after_eat <= data->time_to_die)
	{
		res = eating_times_check(data, i);
		if (res == 0)
			return (0);
		else
			i = res;
	}
	else
	{
		death_announcement(data, i);
		return (0);
	}
	return (i);
}

void	*health_checker(void *data_temp)
{
	int		i;
	t_data	*data;
	int		res;

	i = 0;
	data = (t_data *)data_temp;
	while (check_death(data) == 0)
	{
		while (i < data->philo_count)
		{
			res = supervisor(data, i);
			if (res == 0)
				return ((void *)0);
			else
				i = res;
		}
		i = 0;
	}
	return ((void *)0);
}
