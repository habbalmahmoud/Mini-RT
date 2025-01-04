#include "../includes/miniRT.h"

void minirt(char **av)
{
    char **map;
    t_cor   *cor;

    cor = malloc(sizeof(t_cor));
    map = checking_the_map(av[1]);
    if (validate(map, cor) == 1)
    {
        freearray(map);
        free(cor);
    }
    else
    {
        // printf("a : %f r:%f g:%f b:%f \n", cor->am.am, cor->am.rgb[0], cor->am.rgb[1], cor->am.rgb[2]);
        freearray(map);
        free(cor);
    }
}