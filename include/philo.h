/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:32:05 by arafa             #+#    #+#             */
/*   Updated: 2024/06/26 10:12:49 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
//						  __________			          //
//----------------------/*Structures*\-------------------//

typedef struct s_param
{
	pthread_mutex_t		*fork;
	pthread_mutex_t		death;
	pthread_mutex_t		check_everyone;
	pthread_mutex_t		check_if_dying;
	pthread_mutex_t		start_mutex;
	pthread_mutex_t		print_mutex;
	int					*is_taken;
	int					is_someone_dead;
	int					index;
	int					nb;
	int					everyone_has_eaten;
	long				start;
}	t_param;

typedef struct s_philo
{
	int					id;
	long				dying_time;
	long				eat_time;
	long				sleep_time;
	long				time_end;
	int					nb_of_dining;
	int					has_eaten;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_t			thread;
	t_param				*param;
}	t_philo;
//---------------------\*__________*/-------------------//

//						  __________					 //
//----------------------/*Functions*\-------------------//
int		check_args(int argc, char **input);
//exit
void	exit_manager(char *msg, t_philo *philo);
//tools
long	ft_atoi( char *nptr);
int		ft_strlen(char *str);
void	printf_int_tab(int *tab);
char	*ft_strdup(char *input);
int		is_number(char *input);

//parsing
int		parse_numbers(int argc, char **argv);
void	free_all(t_philo *philo, t_param *param);

//thread
void	init_thread(t_philo *philo, t_param *param);
t_philo	*init_philo(t_philo *philo, t_param *param, char **argv, int argc);
void	end_thread(t_philo *philo, t_param *param);
//usleep
void	ft_sleep(t_philo *philo, char *msg, long sleeping_time);
//debug
void	printf_int_tab(int *tab);
//---------------------\*__________*/-------------------//
#endif