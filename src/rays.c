/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:55:52 by mvocasko          #+#    #+#             */
/*   Updated: 2023/12/04 22:27:12 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/*
//combination of horizontal and vertical movements -> 
//determine direction of ray from p->scene->c
//creates a ray from a p->scene->c's perspective based on
//screen coordinates(x and y)
t_ray	ray_creation(t_p->scene->c *p->scene->c, double x, double y)
{
	t_ray		ray;
	t_vector	move_hor;
	t_vector	move_ver;

	move_hor = vector_scaling(p->scene->c->horizontal, x);
	move_ver = vector_scaling(p->scene->c->vertical, y);
	ray.origin = p->scene->c->origin;
	ray.direction = vector_addition(p->scene->c->bottom_left, move_hor);
	ray.direction = vector_addition(ray.direction, move_ver);
	ray.direction = vector_subtraction(ray.direction, p->scene->c->origin);
	return (ray);
}*/

t_coord	rotate_ray_direction(t_coord dir, t_coord old)
{
	t_coord	new;
	double	angle;

/*	angle = acos(dir.z / sqrt(dir.x * dir.x + dir.z * dir.z));
	if (dir.x < 0)
		angle *= -1;
	ray_dir.x = ray_dir.x * cos(angle) + ray_dir.z * sin(angle);
	ray_dir.z = -ray_dir.x * sin(angle) + ray_dir.z * cos(angle); // changed x
	angle = acos(1 / sqrt(dir.y * dir.y + 1));
	if (dir.y < 0)
		angle *= -1;
	//	if (dir.z < 0)
		//	angle *= -1;
	ray_dir.y = ray_dir.y * cos(angle) - sin(angle);
	ray_dir.z = -ray_dir.y * sin(angle) - cos(angle);*/

	angle = acos(dir.z / sqrt(dir.x * dir.x + dir.z * dir.z));
	if (dir.x < 0)
		angle *= -1;
	new.x = old.x * cos(angle) + old.z * sin(angle);
	new.z = -old.x * sin(angle) + old.z * cos(angle);

	angle = acos(dir.z / sqrt(dir.y * dir.y + dir.z * dir.z));
	//if (dir.y < 0)
		//angle *= -1;


	return (new);
}

// Function to calculate the direction of the ray in p->scene->c space
t_coord	calculate_ray_direction(int pixel_x, int pixel_y, double fov, t_coord dir)
{
	t_coord	ray_dir; // another coord
	double	width;
	double	height;
	double	lens_correction;
	double	phi;
	double	omega;

	width = (double)WIDTH;
	height = (double)HEIGHT;
	lens_correction = tan(deg_to_rad(fov * 0.5));     // should be cos?
	ray_dir.x = lens_correction * (width / height) * (2.0 * (pixel_x + 0.5) / width - 1.0);
	ray_dir.y = lens_correction * ((2.0 * (pixel_y + 0.5) / height - 1.0));
	ray_dir.z = -1.0;                                      // Assuming a simple perspective projection
	//ray_dir = rotate_ray_direction(dir, ray_dir);

	phi = acos(dir.z / sqrt(dir.x * dir.x + dir.z * dir.z));
	omega = atan(dir.y / sqrt((dir.x * dir.x) + (dir.z * dir.z)));
	if (dir.x < 0)
		phi *= -1;
	ray_dir.x = ray_dir.x * cos(phi) - ray_dir.z * sin(phi); // sin phi, cos phi, sin omega, cos omega
	ray_dir.z = ray_dir.x * sin(phi) + ray_dir.z * cos(phi); // changed x
	
	ray_dir.x = ray_dir.x * (cos(omega) + ray_dir.y * sin(omega));
	ray_dir.y = -sin(omega) * (ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z) + ray_dir.y * cos(omega); //
	ray_dir.z = ray_dir.z * (ray_dir.y * sin(omega) + cos(omega));

	//angle = acos(1 / sqrt(dir.y * dir.y + 1));
	//if (dir.y < 0)
	//	angle *= -1;
	////	if (dir.z < 0)
	//	//	angle *= -1;
	//ray_dir.y = ray_dir.y * cos(angle) - sin(angle);
	//ray_dir.z = -ray_dir.y * sin(angle) - cos(angle);
	ray_dir = normalized(ray_dir);
	return (ray_dir);
}

void	pixel_color(t_pointer_mlx *p, double t, int pixel_x, int pixel_y, t_color color) // 5 variables
{
	//does it work in object?
	if (p->pixel_rgb[pixel_x][pixel_y].r == -1
		|| (t < p->pixel_dist[pixel_x][pixel_y] && t >= 0))
	{
		p->pixel_rgb[pixel_x][pixel_y] = color;
        	p->pixel_dist[pixel_x][pixel_y] = t;
	}
}

int	find_shadow(t_pointer_mlx *p, int pixel_x, int pixel_y, t_coord ray_dir)
{
	int	i;
	double	t;

	i = 0;
	while (i < p->scene->n_sp)
	{
		if (intersect_sphere(p->scene->l->pos, ray_dir, p->scene->sp[i], &t) && t < p->pixel_dist[pixel_x][pixel_y])
			return 0;
		i++;
	}
	i = 0;
	while (i < p->scene->n_cy)
	{
		if (intersect_cylinder(p->scene->l->pos, ray_dir, p->scene->cy[i], &t) && t < p->pixel_dist[pixel_x][pixel_y])
			return 0;
		if (intersect_disk(p->scene->l->pos, ray_dir, p->scene->cy[i], &t) && t < p->pixel_dist[pixel_x][pixel_y])
			return 0;
		i++;
	}
	i = 0;
	while (i < p->scene->n_pl)
	{
		if (intersect_plane(p->scene->l->pos, ray_dir, p->scene->pl[i], &t) && t < p->pixel_dist[pixel_x][pixel_y])
			return 0;
		i++;
	}
	return 1;
}

void	find_intersection(t_pointer_mlx *p, int pixel_x, int pixel_y, t_coord ray_dir)
{
	int	i;
	double	t;

	i = 0;
	while (i < p->scene->n_sp)
	{
		if (intersect_sphere(p->scene->c->pos, ray_dir, p->scene->sp[i], &t))
			pixel_color(p, t, pixel_x, pixel_y, p->scene->sp[i]->rgb);
		i++;
	}
	i = 0;
	while (i < p->scene->n_cy)
	{
		if (intersect_cylinder(p->scene->c->pos, ray_dir, p->scene->cy[i], &t))
			pixel_color(p, t, pixel_x, pixel_y, p->scene->cy[i]->rgb);
		if (intersect_disk(p->scene->c->pos, ray_dir, p->scene->cy[i], &t))
			pixel_color(p, t, pixel_x, pixel_y, p->scene->cy[i]->rgb);
		i++;
	}
	i = 0;
	while (i < p->scene->n_pl)
	{
		if (intersect_plane(p->scene->c->pos, ray_dir, p->scene->pl[i], &t))
			pixel_color(p, t, pixel_x, pixel_y, p->scene->pl[i]->rgb);
		i++;
	}
}

void	pixeling(t_pointer_mlx *p)
{
	t_coord	ray_dir;	

	for (int pixel_y = 0; pixel_y < HEIGHT; pixel_y++) {
		for (int pixel_x = 0; pixel_x < WIDTH; pixel_x++) {
			ray_dir = calculate_ray_direction(pixel_x, pixel_y, p->scene->c->fov, p->scene->c->dir);
			find_intersection(p, pixel_x, pixel_y, ray_dir);
			if (find_shadow(p, pixel_x, pixel_y, ray_dir))
			{
//				printf("light\n");
				mlx_put_pixel(p->img, pixel_x, pixel_y, light(&p->pixel_rgb[pixel_x][pixel_y], p->scene->l));
			}
				
			else
			{
//				printf("ambient\n");
				mlx_put_pixel(p->img, pixel_x, pixel_y, ambient(&p->pixel_rgb[pixel_x][pixel_y], p->scene->a));
			}
			//find_shadow(p, pixel_x, pixel_y, ray_dir);
		}
	}
}
