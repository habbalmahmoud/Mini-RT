#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include "../Libft/libft.h"
#include "../GNL/get_next_line.h"
#include "../mlx/mlx.h"
#include "X11/X.h"
#include "X11/keysym.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

typedef struct s_mlbx
{
	void	*mlx;
	void	*mlx_win;
	// t_img	img;
}			t_mlbx;

typedef struct s_light
{
    float			cor[3];
	float			brightness;
}				t_light;

typedef struct s_am
{
    float			am;
	float			rgb[3];
}				t_am;

typedef struct s_cm
{
    float			cor[3];
	float			vector[3];
	float			fov;
}				t_cm;

typedef	struct s_sp
{
    float			cor[3];
	float			rgb[3];
	float		diameter;
}				t_sp;

typedef struct s_cy
{
    float			cor[3];
    float			vector[3];
	float			rgb[3];
	float			cy_diameter;
	float			cy_height;
}				t_cy;

typedef	struct s_pl
{
    float			cor[3];
    float			vector[3];
	float			rgb[3];

}				t_pl;

typedef struct s_map
{
	char	*line;
	struct s_map	*next;
}				t_map;

typedef	struct s_cor
{
	t_am	am;
	t_light light;
	t_cm	cm;
	t_sp	sp;
	t_cy	cy;
	t_pl	pl;

}				t_cor;

typedef struct s_val
{
	bool	a;
	bool	c;
	bool	l;
	bool	sp;
	bool	cy;
	bool	pl;
}				t_val;

char **checking_the_map(char *str);
void minirt(char **av);
int validate(char **map, t_cor *cor);

#endif