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

int	main(int argc, char **argv)
{
	t_data	*data;
	int		failed_index;

	data = NULL;
	if (input_check(argc, argv) != 0)
		return (1);
	data = put_data(argv, data);
	if (!data)
		return (1);
	failed_index = make_table(data);
	destroy_mutexes(data, failed_index);
	free_data(data);
	return (2);
}
