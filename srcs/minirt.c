#include "../includes/miniRT.h"

void minirt(char **av)
{
    char **map;

    map = checking_the_map(av[1]);
    int i = 0;
    while (map[i])
    {
        printf("%s\n", map[i]);
        i++;
    }
}