/*
** main.c for  in /home/thauvi_a/rendu/tek2/PSU_2016_philo
**
** Made by Alexandre Thauvin
** Login   <thauvi_a@epitech.net>
**
** Started on  Mon Mar  6 10:55:43 2017 Alexandre Thauvin
** Last update Mon Mar  6 11:11:31 2017 Alexandre Thauvin
*/

#include <string.h>
#include "philo.h"
#include "extern.h"

int	main(int ac, char **av)
{
  unsigned int	philo;
  unsigned int	chopstick;

  if (ac != 5)
    {
      printf("Usage : philo -p N -e N");
      return (1);
    }
  if (strcmp("-p", av[1]))
  {
    philo = atoi(av[2]);
    chopstick = atoi(av[4]);
  }
  else
  {
    philo = atoi(av[4]);
    chopstick = atoi(av[2]);
  }
  if (philo < 1 || chopstick < 2)
        printf("Usage : philo -p N -e N");
        return (1);
  }
  RCFStartup(ac, av);
  RCFCleanup();
  return (1);
}
