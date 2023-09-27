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

void	make_philo(int index, t_data *data)
{
	data->philo_struct[index].philo_index = index;
	data->philo_struct[index].eating_times = 0;
	data->philo_struct[index].last_time_eat = 0;
	data->philo_struct[index].data = data;
	data->philo_struct[index].died = false;
	pthread_mutex_init(&data->philo_struct[index].lock, NULL);
	pthread_create(&data->philos[index], NULL, &routine, \
	(void *)&data->philo_struct[index]);
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

void	make_table(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		make_philo(i, data);
		i++;
	}
	pthread_create(&data->health_check, NULL, &health_checker, (void *)data);
	join_philos(data->philos, data);
	pthread_join(data->health_check, NULL);
}

void	make_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}
