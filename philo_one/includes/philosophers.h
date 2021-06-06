#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

typedef pthread_mutex_t t_mutex;

typedef struct s_params
{
	int		amount;
	int		t_sleep;
	int		t_eat;
	int		t_die;
	int		t_started;
	int		eat_limit;
	t_mutex	m_stop;
	t_mutex	m_print;	
	t_mutex	*m_forks;
}			t_params;

typedef struct s_philo
{
	int			index;
	int			left_fork;
	int			right_fork;
	int			eat_amount;
	int			last_eat;
	int			t_wdead;
	t_mutex		m_life;
	t_params	*params;
}			t_philo;	

int		init_all(t_philo **tmp, int argc, char *argv[]);
int		print_error(char *str);
int		ft_atoi(char *str);
int 	get_time(void);

void	ft_putnbr(int n);
int		ft_putstr(char *str);
int		ft_putchar(char c);
int		ft_strlen(char *str);
#endif