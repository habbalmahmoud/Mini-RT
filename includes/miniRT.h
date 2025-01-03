#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include "../Libft/libft.h"
#include "../GNL/get_next_line.h"
#include "../mlx/mlx.h"
#include "X11/X.h"
#include "X11/keysym.h"
#include <stdlib.h>
#include <unistd.h>

char **checking_the_map(char *str);
void minirt(char **av);

#endif