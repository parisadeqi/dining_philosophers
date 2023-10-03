/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 15:28:53 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/27 20:11:13 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_failed_philo(t_data *data, int index)
{
	int		i;
	t_data	*temp;

	i = 0;
	temp = data;
	while (i < index)
	{
		pthread_join(data->philos[i], NULL);
		pthread_mutex_destroy(&temp->forks[i]);
		pthread_mutex_destroy(&temp->philo_struct[i].lock);
		pthread_mutex_destroy(&temp->philo_struct[i].time_lock);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->start);
}

void	destroy_mutexes(t_data *data, int index)
{
	int		i;
	t_data	*temp;

	i = 0;
	temp = data;
	if (index == 0)
	{
		pthread_mutex_destroy(&data->write);
		pthread_join(data->health_check, NULL);
		pthread_mutex_destroy(&data->death);
		pthread_mutex_destroy(&data->start);
		while (i < temp->philo_count)
		{
			pthread_mutex_destroy(&temp->forks[i]);
			pthread_mutex_destroy(&temp->philo_struct[i].lock);
			pthread_mutex_destroy(&temp->philo_struct[i].time_lock);
			i++;
		}
	}
	else
		destroy_failed_philo(data, index);
}

void	free_data(t_data *data)
{
	free(data->forks);
	free(data->philo_struct);
	free(data->philos);
	free(data);
}
