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

// Function to calculate the direction of the ray in p->scene->c space
t_coord	calculate_ray_direction(int pixel_x, int pixel_y, double fov, t_coord camera_dir)
{
	t_coord	ray_dir;
	double	width;
	double	height;
	double	lens_correction;

	width = (double)WIDTH;
	height = (double)HEIGHT;
	lens_correction = tan(cos(deg_to_rad(fov * 0.3)));     // should be cos? 0.3 can be changed
	ray_dir.x = lens_correction * (width / height) * (2.0 * (pixel_x + 0.5) / width) - 1.0;
	ray_dir.y = lens_correction * (1.0 - (2.0 * (pixel_y + 0.5) / height));
	ray_dir.z = -1.0;
	printf("camera_dir: %f, %f, %f\n",camera_dir.x, camera_dir.y, camera_dir.z);
	//ray_dir = vector_add(ray_dir, camera_dir);
	//ray_dir = vector_subtract(ray_dir, ray_org);
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
				mlx_put_pixel(p->img, pixel_x, pixel_y, light(&p->pixel_rgb[pixel_x][pixel_y], p->scene->l));
				
			else
				mlx_put_pixel(p->img, pixel_x, pixel_y, ambient(&p->pixel_rgb[pixel_x][pixel_y], p->scene->a));
			//find_shadow(p, pixel_x, pixel_y, ray_dir);
		}
	}
}
