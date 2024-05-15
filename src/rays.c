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

// CREATING RAY PROCESS:

// 1. Normilizing pixel position
//    NCD_x = (x + 0.5) / width
//    NCD_y = (y + 0.5) / height

// 2. Remapping the pixels from range [0:1] to [-1;1]
//    pixelscreen_x = 2 * NCD_x - 1  
//    pixelscreen_y = 1 - 2 * NCD_y

// 3. Adjust to aspect ratio of screen
//    ratio = width / height
//    pixelcamera_x = (2 * pixelscreen_x - 1) * ratio * tan(fov / 2)
//    pixelcamera_y = 1 - 2 * pixelscreen_y * tan(fov / 2)

//    camera_space = (pixelcamera_x, pixelcamera_y, -1)

// https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html
t_coord	creating_ray(int pixel_x, int pixel_y, double fov, t_coord dir)
{
	//t_coord	camera_space;
	t_coord	ray_dir;
	double	width;
	double	height;
	double	fov_to_height;
	//double	phi;
	//double	omega;

	width = (double)WIDTH;
	height = (double)HEIGHT;
	fov_to_height = tan(deg_to_rad(fov * 0.5));     // should be cos?
	ray_dir.x = fov_to_height * (width / height) * (2.0 * (pixel_x + 0.5) / width - 1.0);
	ray_dir.y = fov_to_height * (1.0 - 2.0 * (pixel_y + 0.5) / height);
	ray_dir.z = -1.0;

	//ray_dir = normalized(ray_dir);
	/*phi = acos(dir.z / sqrt(dir.x * dir.x + dir.z * dir.z));
	omega = atan(dir.y / sqrt((dir.x * dir.x) + (dir.z * dir.z)));
	if (dir.x < 0)
		phi *= -1;
	ray_dir.x = ray_dir.x * cos(phi) - ray_dir.z * sin(phi); // sin phi, cos phi, sin omega, cos omega
	ray_dir.z = ray_dir.x * sin(phi) + ray_dir.z * cos(phi); // changed x
	
	ray_dir.x = ray_dir.x * (cos(omega) + ray_dir.y * sin(omega));
	ray_dir.y = -sin(omega) * (ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z) + ray_dir.y * cos(omega);
	ray_dir.z = ray_dir.z * (ray_dir.y * sin(omega) + cos(omega));*/
	
	printf("%f", dir.x);
	//ray_dir = normalized(ray_dir);
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
			ray_dir = creating_ray(pixel_x, pixel_y, p->scene->c->fov, p->scene->c->dir);
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
