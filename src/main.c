/*
** main.c for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Mon Mar  6 10:55:43 2017 Alexandre Thauvin
** Last update Tue Mar  7 23:31:11 2017 Paul THEIS
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "philo.h"
#include "extern.h"
#include "../include/philo.h"
#include "../include/extern.h"

pthread_barrier_t mutex_stock;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void     *print_philo (void *phil)
{
  t_philo	    *philo;
  int		    s;

  philo = (t_philo *)phil;
  // Attendre que les nbPhilo soit là avant de continuer.
  s = pthread_barrier_wait(&mutex_stock);
  pthread_mutex_lock(&mutex);
  if(s == 0) {
    printf("Thread %ld passed barrier %d: return value was 0\n", philo->thread, philo->id);
  } else if (s == PTHREAD_BARRIER_SERIAL_THREAD) {
    printf("Thread %ld passed barrier %d: return value was PTHREAD_BARRIER_SERIAL_THREAD\n", philo->thread, philo->id);
  } else {
    printf("pthread_barrier_wait (%ld)", philo->thread);
    exit(EXIT_FAILURE);
  }
  printf("+-------------------------------+\n");
  printf("| PHILO \t%-16d|\n", philo->id);
  printf("+-------------------------------+\n");
  printf("| Thread: \t%-16ld|\n", philo->thread);
  printf("| end: \t\t%-16p|\n", philo->end);
  printf("| chopstick: \t%-16s|\n", (philo->chopstick) ? "true" : "false");
  printf("| Right: \t%-16p|\n", philo->right);
  printf("| State: \t%-16d|\n", philo->state);
  printf("| count: \t%-16d|\n", philo->count);
  printf("| id: \t\t%-16d|\n", philo->id);
  printf("+-------------------------------+\n");
  printf("| addr: \t%-16p|\n", philo);
  printf("+-------------------------------+\n");
  usleep(10);
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
  lphilo_eat();
  return (NULL);
}

int		    philo(int nbPhilo, int nbEat)
{
  int 		i;
  int  		end;
  t_philo 	philos[nbPhilo];

  i = -1;
  end = 0;
  // Initialisation de la barriere a nbPhilo de philo.
  pthread_barrier_init(&mutex_stock, NULL, nbPhilo);
  // Boucle permettant de creer tous les philo.
  while (++i < nbPhilo)
    {
      philos[i].right = (i == nbPhilo - 1) ? (&philos[0]) : (&philos[i + 1]);
      philos[i].state = REST;
      philos[i].count = nbEat;
      philos[i].chopstick = true;
      philos[i].id = i;
      philos[i].end = &end;
      pthread_mutex_init(&philos[i].mutex, NULL); //PTHREAD_MUTEX_INITIALIZER;
      if (pthread_create(&philos[i].thread, NULL, print_philo, &philos[i]))
        return (fprintf(stderr,"Error - pthread_create() return code: %d\n", -1), 1);
  }
  // La boucle qui suit permet d'attendre la fin de tous les threads.
  i = 0;
  while (i < nbPhilo)
    if (pthread_join(philos[i++].thread, NULL))
      return (fprintf(stderr, "Error - pthread_join()\n"), 1);
  return (0);
}

int			    main(int ac, char **av)
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
