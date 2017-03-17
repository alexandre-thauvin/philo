/*
** philo.h for  in /home/aneopsy/PSU_2016_philo/include/
**
** Made by Paul THEIS
** Login   <theis_p@epitech.eu>
**
** Started on  Thu Mar  9 21:46:14 2017 Paul THEIS
** Last update Mon Mar 13 14:36:55 2017 Paul THEIS
*/

#ifndef PHILO_H_
# define PHILO_H_

#include <pthread.h>
#include <stdbool.h>

#include "extern.h"

enum STATE {SLEEP,
            EAT,
            THINK};

typedef struct		s_philo
{
  pthread_t		thread;
  pthread_mutex_t	chopstick;
  pthread_barrier_t 	*barrier;
  struct s_philo	*right;
  enum STATE		state;
  bool			*flg;
  int			count;
}			t_philo;

#endif /* !PHILO_H_ */
