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

int	first_fork_lock(t_philo *philo)
{
	if (check_death(philo->data) != 0)
		return (1);
	if ((philo->philo_index + 1) % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo->philo_index + 1, \
		"has taken a fork", philo->data);
	}
	if ((philo->philo_index + 1) % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo->philo_index + 1, \
		"has taken a fork", philo->data);
	}
	return (0);
}

void	second_fork_lock(t_philo *philo)
{
	if ((philo->philo_index + 1) % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo->philo_index + 1, \
		"has taken a fork", philo->data);
	}
	if ((philo->philo_index + 1) % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo->philo_index + 1, \
		"has taken a fork", philo->data);
	}
	return ;
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

int	make_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (i >= 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}
