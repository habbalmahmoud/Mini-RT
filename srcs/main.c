#include "../includes/miniRT.h"


void make_window()
{
    t_mlbx *mlbx;

    mlbx = malloc(sizeof(t_mlbx));
    mlbx->mlx = mlx_init();
	mlbx->mlx_win = mlx_new_window(mlbx->mlx, 1200, 720, "MiniRT");
    mlx_loop(mlbx->mlx);    
}

int main(int ac, char **av)
{
    if (ac != 2)
        printf("Error\nOnly 2 Arguments Required !\n");
    else
    {
        minirt(av);
        make_window();
    }
    return (0);
}