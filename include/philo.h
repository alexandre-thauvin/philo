//
// created by thauvi_a
//

#ifndef PHILO_H_
# define PHILO_H_

#include <pthread.h>
#include <stdbool.h>

enum STATE { REST, EAT, THINK };

typedef struct		s_philo
{
  pthread_t		thread;
  int			*end;
  pthread_mutex_t	mutex;
  bool			chopstick;
  struct s_philo	*right;
  enum STATE		state;
  int			nbEat;
  int			id;
}			t_philo;

#endif /* !PHILO_H_ */
