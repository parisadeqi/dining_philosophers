/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prepare_philos.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 15:32:39 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/27 20:15:25 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(int index, t_data *data)
{
	data->philo_struct[index].philo_index = index;
	data->philo_struct[index].eating_times = 0;
	data->philo_struct[index].last_time_eat = 0;
	data->philo_struct[index].data = data;
	data->philo_struct[index].died = false;
	if (pthread_mutex_init(&data->philo_struct[index].lock, NULL) != 0)
	{
		printf("pthread_mutex_init function failed!\n");
		return (index);
	}
	if (pthread_mutex_init(&data->philo_struct[index].time_lock, NULL) != 0)
	{
		printf("pthread_mutex_init function failed!\n");
		return (index);
	}
	if (pthread_create(&data->philos[index], NULL, &routine, \
	(void *)&data->philo_struct[index]) != 0)
	{
		printf("pthread_create function failed!\n");
		return (index);
	}
	return (0);
}

void	join_philos(pthread_t *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
}

int	make_table(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->start);
	while (i < data->philo_count)
	{
		if (make_philo(i, data) != 0)
		{
			pthread_mutex_lock(&data->write);
			pthread_mutex_lock(&data->death);
			data->dead_philo = true;
			pthread_mutex_unlock(&data->death);
			pthread_mutex_unlock(&data->write);
			pthread_mutex_unlock(&data->start);
			return (i);
		}
		i++;
	}
	data->start_time = get_time_ms();
	pthread_mutex_unlock(&data->start);
	pthread_create(&data->health_check, NULL, \
	&health_checker, (void *)data);
	join_philos(data->philos, data);
	pthread_join(data->health_check, NULL);
	return (0);
}
