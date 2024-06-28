/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:19:52 by jmougel           #+#    #+#             */
/*   Updated: 2024/03/22 07:56:06 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

# define ERROR		"\e[31mError\e[0m\n"
# define BAD_ARGS	"philo: bad number of args\n./philo <nbr_philo>\
 <time_to_die> <time_to_eat> <time_to_sleep>"
# define BAD_FORMAT	"philo: bad format, philo takes only digits characters"
# define BAD_LIMITS	"philo: limits reached, philo takes only until 200\
 philo and from 0 to INT_MAX for others args"

typedef struct s_philos
{
	bool			thinking;
	bool			fork_r;
	bool			fork_l;
	bool			last;
	int				index;
	int				nbr_eat;
	int				nbr_fork;
	size_t			last_meal;
	pthread_t		tid;
	struct s_data	*data;
	struct s_philos	*next;
	struct s_philos	*prev;
	pthread_mutex_t	mutex_fork_r;
	pthread_mutex_t	*mutex_fork_l;
}	t_philos;

typedef struct s_data
{
	void			*f;
	bool			death;
	size_t			current_time;
	size_t			start_time;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	mutex_time;
	pthread_mutex_t	mutex_start;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	mutex_check;
	struct s_philos	*lst;
	struct s_info	*info;
}	t_data;

typedef struct s_info
{
	size_t	nbr_philo;
	size_t	die_time;
	size_t	eat_time;
	size_t	sleep_time;
	int		nbr_eat;
}	t_info;

/*Init*/
t_philos	*init_philos(t_data *data);
t_data		*init_data(t_info *info);
t_info		init_info(int argc, char**argv);
int			create_threads(t_data *data);
void		init_mutex(t_data *data);
/**/

/*Check*/
int			check_digit(char **argv);
int			if_all_ate(t_data *data);
int			check_args(t_info *info);
void		if_philo_died(t_data *data);
/**/

/*Routine*/
void		*thread_routine(void *d);
/**/

/*Forks*/
void		taking_fork_r(t_data *data, t_philos *current_philo);
void		taking_fork_l(t_data *data, t_philos *current_philo);
void		let_fork_r(t_philos *current_philo);
void		let_fork_l(t_philos *current_philo);
/**/

/*Utils*/
size_t		get_current_time(void);
int			ft_atoi(const char *nptr);
int			ft_usleep(size_t milliseconds, t_data *data);
void		ft_putstr_fd(char *s, int fd);
void		print_msg(char *str, t_data *data, t_philos *philo, bool death);
/**/

/*Errors*/
int			ft_exit(char *str, int fd, t_philos *lst, t_data *data);
void		free_philos(t_philos **lst);
int			error_msg(char *str);
/**/

/*Lst utils*/
t_philos	*ft_lstnew(int index, t_data *data);
t_philos	*ft_lstlast(t_philos *lst);
int			ft_lstadd_back(t_philos **lst, t_philos *new);
/**/

#endif
