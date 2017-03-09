#include "extern.h"
#include "philo.h"

void      eat(t_philo *philo)
{
  if (pthread_mutex_trylock(&philo->mutex) &&
        pthread_mutex_trylock(&philo->right->mutex))
      {
        philo->chopstick = false;
        philo->right->chopstick = false;
        lphilo_take_chopstick(&philo->mutex);
        lphilo_take_chopstick(&philo->right->mutex);
        philo->state = EAT;
        lphilo_eat();
        philo->count -= 1;
        lphilo_release_chopstick(&philo->mutex);
        lphilo_release_chopstick(&philo->right->mutex);
        pthread_mutex_unlock(&philo->mutex);
        pthread_mutex_unlock(&philo->right->mutex);
        philo->right->chopstick = true;
        philo->right->chopstick = true;
      }
}

void      think(t_philo *philo)
{
  //trylock
  //chopstick false
  // state think
  //take
  //think
  //release
  //unlock
  //chopstick true
  //--
  // meme processus avec celui de droite
  if (pthread_mutex_trylock(&philo->mutex) && philo->right->state != THINK)
    {
      philo->chopstick = false;
      philo->state = THINK;
      lphilo_take_chopstick(&philo->mutex);
      lphilo_think();
      lphilo_release_chopstick(&philo->mutex);
      pthread_mutex_unlock(&philo->mutex);
      philo->chopstick = true;
    }
  else if (pthread_mutex_trylock(&philo->right->mutex)
	   && philo->right->state != THINK)
    {
      philo->chopstick = false;
      philo->state = THINK;
      lphilo_take_chopstick(&philo->right->mutex);
      lphilo_think();
      lphilo_release_chopstick(&philo->right->mutex);
      pthread_mutex_unlock(&philo->right->mutex);
      philo->chopstick = true;
    }
}

void      rest(t_philo *philo)
{
  philo->state = REST;
  lphilo_sleep();
}
