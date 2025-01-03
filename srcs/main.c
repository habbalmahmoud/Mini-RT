#include "../includes/miniRT.h"

int main(int ac, char **av)
{
    if (ac != 2)
        printf("Error\nOnly 2 arguments required\n");
    else
        minirt(av);
    return (0);
}