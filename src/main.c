/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:30:54 by arafa             #+#    #+#             */
/*   Updated: 2024/06/26 08:32:40 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death(t_philo *philo);

int	ft_check(t_param *param);

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_param	param;
	int		i;

	philo = NULL;
	check_args(argc, argv);
	philo = init_philo(philo, &param, argv, argc);
	init_thread(philo, &param);
	while (!ft_check(&param))
	{
		i = -1;
		while (++i < param.nb)
		{
			if (param.nb == param.everyone_has_eaten)
			{
				pthread_mutex_lock(&param.check_if_dying);
				param.is_someone_dead = 1;
				pthread_mutex_unlock(&param.check_if_dying);
				break ;
			}
			if (ft_death(&philo[i]))
				break ;
		}
	}
	end_thread(philo, philo[0].param);
}
