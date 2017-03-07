/*
** main.c for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Mon Mar  6 10:55:43 2017 Alexandre Thauvin
** Last update Tue Mar  7 17:42:27 2017 Paul THEIS
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "philo.h"
#include "extern.h"

pthread_mutex_t mutex_stock;

static void * print_philo (void * phil)
{
  t_philo	*philo;

  while (1)
  {
  pthread_mutex_lock(&mutex_stock);
  philo = phil;
  printf("#----- PHILO -----#\n");
  printf("Thread: %ld\n", philo->thread);
  printf("end: %p\n", philo->end);
  printf("chopstick: %d\n", philo->chopstick);
  printf("Right: %p\n", philo->right);
  printf("State: %d\n", philo->state);
  printf("nbEat: %d\n", philo->nbEat);
  printf("id: %d\n", philo->id);
  printf("#-----------------#\n");
  pthread_mutex_unlock(&mutex_stock);
      }
  pthread_exit(NULL);
  return (NULL);
}

int		philo(int nbPhilo, int nbEat)
{
  int 		i;
  t_philo 	philos[nbPhilo];
  int  		end;

  i = -1;
  end = 0;
  while (++i < nbPhilo)
    {
      philos[i].right = (i == nbPhilo - 1) ? (&philos[0]) : (&philos[i + 1]);
      philos[i].state = REST;
      philos[i].nbEat = nbEat;
      philos[i].chopstick = true;
      philos[i].id = i;
      philos[i].end = &end;
      if (pthread_create(&philos[i].thread, NULL, print_philo, &philos[i]))
	{
	  fprintf(stderr,"Error - pthread_create() return code: %d\n", -1);
	  exit(EXIT_FAILURE);
	}
  }
  i = 0;
  return (0);
}

int			main(int ac, char **av)
{
  int			nbPhilo;
  int			nbChopstick;
  int			i;

  i = 0;
  RCFStartup(ac, av);
  while (i < ac)
    {
      if (strcmp(av[i], "-p") == 0 && i + 1 < ac)
        nbPhilo = atoi(av[i + 1]);
      if (strcmp(av[i], "-e") == 0 && i + 1 < ac)
        nbChopstick = atoi(av[i + 1]);
      ++i;
    }
  if (nbPhilo < 1 || nbChopstick < 2)
    return (printf("Usage : philo -p N -e N"), 1);
  philo(nbPhilo, nbChopstick);
  RCFCleanup();
  return (0);
}
