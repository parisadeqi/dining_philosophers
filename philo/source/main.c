/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 15:55:08 by psadeghi      #+#    #+#                 */
/*   Updated: 2023/09/27 20:17:11 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int		i;
	t_data	*temp;

	i = 0;
	temp = data;
	pthread_mutex_destroy(&data->write);
	pthread_detach(data->health_check);
	pthread_mutex_destroy(&data->death);
	while (i < temp->philo_count)
	{
		pthread_mutex_destroy(&temp->forks[i]);
		pthread_mutex_destroy(&temp->philo_struct[i].lock);
		i++;
	}
}

void	free_data(t_data *data)
{
	free(data->forks);
	free(data->philo_struct);
	free(data->philos);
	free(data);
}

t_data	*put_data(char **argv, t_data *data)
{
	data = malloc(sizeof(t_data));
	data->count_must_eat = 0;
	data->dead_philo = false;
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = get_time_ms();
	data->count_must_eat = 0;
	if (argv[5])
		data->count_must_eat = ft_atoi(argv[5]);
	data->philo_struct = malloc(sizeof(t_philo) * data->philo_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->philo_count));
	make_forks(data);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->death, NULL);
	data->philos = malloc(sizeof(pthread_t) * (data->philo_count));
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
	{
		printf("Please put the right amout of arguments:D\n");
		return (-1);
	}
	data = NULL;
	data = put_data(argv, data);
	make_table(data);
	destroy_mutexes(data);
	free_data(data);
	return (2);
}
