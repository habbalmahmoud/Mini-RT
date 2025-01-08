#include "../includes/miniRT.h"


void minirt(char **av)
{
    char **map;
    t_cor   *cor;

    cor = malloc(sizeof(t_cor));
    map = checking_the_map(av[1]);
    if (map != NULL && validate(map, cor) == 1)
    {
        freearray(map);
        free(cor);
    }
    else
    {
        if(map != NULL)
            freearray(map);
        free(cor);
    }
}