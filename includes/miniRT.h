#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <math.h>
#include "../Libft/libft.h"
#include "../GNL/get_next_line.h"
#include "../mlx/mlx.h"
#include "X11/X.h"
#include "X11/keysym.h"
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

# define HEIGHT 700
# define WIDTH 1000

typedef struct s_mlx
{
	void		*ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;

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


		// VALIDATION
char **checking_the_map(char *str);
int validate(char **map, t_cor *cor);


		// WINDOW
void minirt(char **av);
void create_window(t_mlx *mlx, t_cor *cor);

		// RAYTRACING HELPERS
void	put_pixel(t_mlx *mlx, int x, int y, int color);
float	dot_product(float v1[3], float v2[3]);
void	normalize(float v[3]);
int		ray_intersects_sphere(float origin[3], float dir[3], t_sp sphere, float *t);
void	render_scene(t_mlx *mlx, t_cor *cor);
#endif