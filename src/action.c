/*
** action.c for  in /home/aneopsy/PSU_2016_philo/src/
**
** Made by Paul THEIS
** Login   <theis_p@epitech.eu>
**
** Started on  Thu Mar  9 22:20:51 2017 Paul THEIS
** Last update Fri Mar 10 18:28:40 2017 Paul THEIS
*/

#include "philo.h"

void		p_eat(t_philo *philo)
{
  if (pthread_mutex_trylock(&philo->mutex) &&
      pthread_mutex_trylock(&philo->right->mutex))
    {
      lphilo_take_chopstick(&philo->right->mutex);
      lphilo_take_chopstick(&philo->mutex);
      lphilo_eat();
      lphilo_release_chopstick(&philo->right->mutex);
      lphilo_release_chopstick(&philo->mutex);
      pthread_mutex_unlock(&philo->right->mutex);
      pthread_mutex_unlock(&philo->mutex);
      --philo->count;
      philo->state = EAT;
    }
}

void		p_think(t_philo *philo)
{
  if (pthread_mutex_trylock(&philo->mutex))
    {
      lphilo_take_chopstick(&philo->mutex);
      lphilo_think();
      lphilo_release_chopstick(&philo->mutex);
      pthread_mutex_unlock(&philo->mutex);
      philo->state = THINK;
    }
  else if (pthread_mutex_trylock(&philo->right->mutex))
    {
      lphilo_take_chopstick(&philo->right->mutex);
      lphilo_think();
      lphilo_release_chopstick(&philo->right->mutex);
      pthread_mutex_unlock(&philo->right->mutex);
      philo->state = THINK;
    }
}

void		p_sleep(t_philo *philo)
{
  lphilo_sleep();
  philo->state = SLEEP;
}
