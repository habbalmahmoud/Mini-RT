/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:40:15 by marvin            #+#    #+#             */
/*   Updated: 2025/01/31 16:40:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <math.h>

int del_app(t_mlx *mlx)
{
    if (mlx->win_ptr)
        mlx_destroy_window(mlx->ptr, mlx->win_ptr);
    if (mlx->ptr)
        mlx_destroy_display(mlx->ptr);
    free(mlx->ptr);
    exit(0);
    return (0);
}


int	key_press(int keysym, t_mlx *mlx)
{
	if (keysym == 65307)
		del_app(mlx);
	return (1);
}

float dot_product(float v1[3], float v2[3])
{
	float dot;
	int i;

	dot = 0.0;
	i = 0;
	while (i < 3)
	{
		dot += v1[i] * v2[i];
		i++;
	}
	return (dot);
}

void normalize(float v[3])
{
	float length;
	int i;

	length = sqrt(dot_product(v, v));
	if (length == 0)
		return ;
	i = 0;
	while (i < 3)
	{
		v[i] /= length;
		i++;
	}
}

/* ---------------- put_pixel() ---------------- */
/* Puts a pixel into the MLX image. */
void put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/* ---------------- Ray-Sphere Intersection ---------------- */
/*
	Calculates the intersection of a ray with a sphere.
	origin: camera origin
	dir: normalized ray direction
	sphere: sphere from scene (center stored in sphere.cor, radius = diameter/2)
	*t: intersection distance (if hit)
	Returns 1 if an intersection occurs, 0 otherwise.
*/
int ray_intersects_sphere(float origin[3], float dir[3], t_sp sphere, float *t)
{
	float oc[3];
	float a;
	float b;
	float c;
	float discriminant;
	float radius;
	int i;

	radius = sphere.diameter / 2.0;
	i = 0;
	while (i < 3)
	{
		oc[i] = origin[i] - sphere.cor[i];
		i++;
	}
	a = dot_product(dir, dir);
	b = 2.0 * dot_product(oc, dir);
	c = dot_product(oc, oc) - (radius * radius);
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (0);
	*t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (*t < 0)
		*t = (-b + sqrt(discriminant)) / (2.0 * a);
	if (*t < 0)
		return (0);
	return (1);
}

/* ---------------- Render Scene ---------------- */
/*
	Simple raytracer that loops over every pixel,
	computes a ray from the camera (assumed at (0,0,0)),
	and tests for intersection with the sphere defined in cor->sp.
	We compute a basic diffuse shading with the light from cor->light.
*/
void render_scene(t_mlx *mlx, t_cor *cor)
{
	int		x;
	int		y;
	float	t;
	float	origin[3];
	float	dir[3];
	float	viewport_width;
	float	viewport_height;
	float	fov_rad;
	float	aspect_ratio;
	float	u, v;
	float	hit_point[3];
	float	normal[3];
	float	light_dir[3];
	float	diffuse;
	int		color;
	int		i;

	/* Camera origin: if you have a camera in cor->cm, you can use that instead */
	origin[0] = 0.0;
	origin[1] = 0.0;
	origin[2] = 0.0;

	aspect_ratio = (float)WIDTH / (float)HEIGHT;
	/* Using the camera fov if available; otherwise use 90 degrees */
	fov_rad = (cor->cm.fov > 0 ? (cor->cm.fov * M_PI / 180.0) : (M_PI / 2.0));
	viewport_height = 2.0 * tan(fov_rad / 2.0);
	viewport_width = aspect_ratio * viewport_height;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			/* Map pixel coordinate (x,y) to viewport coordinate (u,v) */
			u = ((float)x + 0.5) / (float)WIDTH;
			v = ((float)y + 0.5) / (float)HEIGHT;
			/* Calculate ray direction.
			   We assume the viewport is at z = -1.
			   Center of viewport is (0,0,-1). */
			dir[0] = (u * viewport_width) - (viewport_width / 2.0);
			dir[1] = ((1.0 - v) * viewport_height) - (viewport_height / 2.0);
			dir[2] = 1.0;
			normalize(dir);

			if (ray_intersects_sphere(origin, dir, cor->sp, &t))
			{
				/* Compute hit point = origin + t * dir */
				i = 0;
				while (i < 3)
				{
					hit_point[i] = origin[i] + t * dir[i];
					i++;
				}
				/* Compute normal at hit point: (hit_point - sphere center) / radius */
				i = 0;
				while (i < 3)
				{
					normal[i] = (hit_point[i] - cor->sp.cor[i]) / (cor->sp.diameter / 2.0);
					i++;
				}
				normalize(normal);
				/* Compute light direction: light position - hit point */
				i = 0;
				while (i < 3)
				{
					light_dir[i] = cor->light.cor[i] - hit_point[i];
					i++;
				}
				normalize(light_dir);
				/* Diffuse shading: clamp dot product */
				diffuse = dot_product(normal, light_dir);
				if (diffuse < 0)
					diffuse = 0;
				/* Simple shading: apply light brightness */
				diffuse *= cor->light.brightness;
				/* Compute final color by modulating sphere color */
				/* Convert each color channel (r, g, b) to int.
				   Assume sphere.rgb[] is in the range [0,255]. */
				color = (((int)(cor->sp.rgb[0] * diffuse) & 0xFF) << 16)
						| (((int)(cor->sp.rgb[1] * diffuse) & 0xFF) << 8)
						| ((int)(cor->sp.rgb[2] * diffuse) & 0xFF);
				put_pixel(mlx, x, y, color);
			}
			/* Else: leave the pixel black (0x000000) */
			else
				put_pixel(mlx, x, y, 0x000000);
			x++;
		}
		y++;
	}
    if (ray_intersects_sphere(origin, dir, cor->sp, &t))
    {
        printf("Hit sphere at t = %f\n", t);
    }

	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr, mlx->img, 0, 0);
}

/* ---------------- Modified create_window() ---------------- */
/*
	This function now creates an image, calls render_scene() to raytrace the sphere,
	and sets up the MLX hooks.
	We now pass the scene data (t_cor) so that the parsed sphere (sp) and light
	information is used.
*/
void create_window(t_mlx *mlx, t_cor *cor)
{
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
	{
		printf("ERROR\nMLX INIT\n");
		return;
	}
	mlx->win_ptr = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win_ptr)
	{
		free(mlx->ptr);
		printf("Error\nWindow Error\n");
		return;
	}
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
		&mlx->line_length, &mlx->endian);

	render_scene(mlx, cor);

	mlx_hook(mlx->win_ptr, KeyRelease, KeyReleaseMask, &key_press, mlx);
	mlx_hook(mlx->win_ptr, DestroyNotify, StructureNotifyMask, &del_app, mlx);
	mlx_loop(mlx->ptr);
}