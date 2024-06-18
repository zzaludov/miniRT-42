/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:55:52 by zzaludov          #+#    #+#             */
/*   Updated: 2024/05/15 20:31:23 by zzaludov         ###   ########.fr       */
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
t_coord	creating_ray(int pixel_x, int pixel_y, double fov/*, t_coord dir*/)
{
	//t_coord	camera_space;
	t_coord	ray_dir;
	double	width;
	double	height;
	double	fov_to_height;
//	double	phi;
//	double	omega;

	width = (double)WIDTH;
	height = (double)HEIGHT;
	fov_to_height = tan(deg_to_rad(fov * 0.5));
	ray_dir.x = fov_to_height * (width / height) * (2.0 * (pixel_x + 0.5) / width - 1.0);
	ray_dir.y = fov_to_height * (1.0 - 2.0 * (pixel_y + 0.5) / height);
	ray_dir.z = -1.0;

	/*ray_dir = normalized(ray_dir);
	phi = acos(dir.z / sqrt(dir.x * dir.x + dir.z * dir.z));
	omega = atan(dir.y / sqrt((dir.x * dir.x) + (dir.z * dir.z)));
	if (dir.x < 0)
		phi *= -1;
	ray_dir.x = ray_dir.x * cos(phi) - ray_dir.z * sin(phi); // sin phi, cos phi, sin omega, cos omega
	ray_dir.z = ray_dir.x * sin(phi) + ray_dir.z * cos(phi); // changed x
	
	ray_dir.x = ray_dir.x * (cos(omega) + ray_dir.y * sin(omega));
	ray_dir.y = -sin(omega) * (ray_dir.x * ray_dir.x + ray_dir.z * ray_dir.z) + ray_dir.y * cos(omega);
	ray_dir.z = ray_dir.z * (ray_dir.y * sin(omega) + cos(omega));*/
	
	//printf("%f", dir.x);
	ray_dir = normalized(ray_dir);
	return (ray_dir);
}

//t_pixel	pixel_color(t_pointer_mlx *p, double t, int pixel_x, int pixel_y, t_color color) // 5 variables
t_pixel	pixel_info(t_pixel *prev, t_color color, double dist, char object, int index)
{
	t_pixel	pixel;

	if (prev->rgb.r == -1
		|| (dist < prev->cam_dist && dist >= 0))
	{
		pixel.rgb = color;
        	pixel.cam_dist = dist;
		pixel.object = object;
		pixel.index = index;
	}
	else
		pixel = *prev;
	return (pixel); //add center pos
}

/*int	between(int t, int dist)
{
	return(1);
}*/

int	find_shadow(t_pointer_mlx *p, int x, int y, t_coord light_dir)
{
	int	i;
	double	t;
	t_coord	bias;
	
	bias = vector_add(p->scene->l->pos, vector_scale(light_dir, -1 * EPSILON));
	i = 0;
	while (i < p->scene->n_sp)
	{
		if ((i != p->pixel[x][y].index && p->pixel[x][y].object != 's')
			&& intersect_sphere(bias, light_dir, p->scene->sp[i], &t)
			&& t > 0 && t < p->pixel[x][y].light_dist)
			return (0);
		i++;
	}
	i = 0;
	while (i < p->scene->n_cy)
	{
		if ((p->pixel[x][y].object != 'c' || p->pixel[x][y].index != i)
			&& intersect_cylinder(bias, light_dir, p->scene->cy[i], &t)
			 && t > 0 && t < p->pixel[x][y].light_dist)
			return (0);
		if ((p->pixel[x][y].object != 'd' || p->pixel[x][y].index != i)
			&& intersect_disk(bias, light_dir, p->scene->cy[i], &t)
			 && t > 0 && t < p->pixel[x][y].light_dist)
				return (0);
		i++;
	}
	i = 0;
	while (i < p->scene->n_pl)
	{

		if ((p->pixel[x][y].object != 'p' && p->pixel[x][y].index != i)
			&& intersect_plane(bias, light_dir, p->scene->pl[i], &t)
			&& t > 0 && t < p->pixel[x][y].light_dist)
				return (0);
		i++;
	}
	return 1;
}

double	find_intersection(t_pointer_mlx *p, int x, int y, t_coord ray_dir)
{
	int	i;
	double	t;

	i = 0;
	while (i < p->scene->n_sp)
	{
		if (intersect_sphere(p->scene->c->pos, ray_dir, p->scene->sp[i], &t))
			p->pixel[x][y] = pixel_info(&p->pixel[x][y], p->scene->sp[i]->rgb, t, 's', i);
		i++;
	}
	i = 0;
	while (i < p->scene->n_cy)
	{
		if (intersect_cylinder(p->scene->c->pos, ray_dir, p->scene->cy[i], &t))
			p->pixel[x][y] = pixel_info(&p->pixel[x][y], p->scene->cy[i]->rgb, t, 'c', i);
		if (intersect_disk(p->scene->c->pos, ray_dir, p->scene->cy[i], &t))
			p->pixel[x][y] = pixel_info(&p->pixel[x][y], p->scene->cy[i]->rgb, t, 'd', i);
		i++;
	}
	i = 0;
	while (i < p->scene->n_pl)
	{
		if (intersect_plane(p->scene->c->pos, ray_dir, p->scene->pl[i], &t))
			p->pixel[x][y] = pixel_info(&p->pixel[x][y], p->scene->pl[i]->rgb, t, 'p', i);
		i++;
	}
	return (t);
}

void	calculate_normal(t_scene *s, t_pixel *pixel)
{
	t_coord	cp;
	double	projection_lenght;
	t_coord	projection;
	t_coord	projection_point;

	if(pixel->object == 's')
		pixel->normal = normalized(vector_subtract(pixel->intersection, s->sp[pixel->index]->pos));
	else if(pixel->object == 'c')
	{
		cp = vector_subtract(pixel->intersection, s->cy[pixel->index]->pos);
		projection_lenght = vector_point(cp, s->cy[pixel->index]->dir);
		projection = vector_scale(s->cy[pixel->index]->dir, projection_lenght);
		projection_point = vector_add(s->cy[pixel->index]->pos, projection);
		pixel->normal = normalized(vector_subtract(pixel->intersection, projection_point));
	}
	else if(pixel->object == 'd')
		pixel->normal = s->cy[pixel->index]->dir;
	else if(pixel->object == 'p')
		pixel->normal = s->pl[pixel->index]->dir;
}

// https://brilliant.org/wiki/3d-coordinate-geometry-equation-of-a-line/

void	pixeling(void *param)
{
	t_pointer_mlx *p;
	t_coord	ray_dir;
	t_coord	light_dir;
	int	i;

	p = param;
	double	t;
	t_color	final;

	i = 0;
	while (i < WIDTH)
		free(p->pixel[i++]);
	free(p->pixel);
	pixel_struct(p);
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			ray_dir = creating_ray(x, y, p->scene->c->fov/*, p->scene->c->dir*/);
			t = find_intersection(p, x, y, ray_dir);

			// intersection point in 3D coordinates
			p->pixel[x][y].intersection = vector_scale(ray_dir, t);
			p->pixel[x][y].intersection = vector_add(p->pixel[x][y].intersection, p->scene->c->pos);
			calculate_normal(p->scene, &p->pixel[x][y]);
			
			light_dir = vector_subtract(p->pixel[x][y].intersection, p->scene->l->pos);
			
			p->pixel[x][y].light_dist = vector_len(light_dir);
			light_dir = normalized(light_dir);

			if (vector_point(p->pixel[x][y].normal, light_dir) < 0) 
        		p->pixel[x][y].normal = vector_scale(p->pixel[x][y].normal, -1);
			
			if (p->pixel[x][y].index != -1 && find_shadow(p, x, y, light_dir))
				final = diffuse(p->pixel[x][y], p->scene->a, p->scene->l, light_dir);
			else
				final = ambient(&p->pixel[x][y].rgb, p->scene->a);
			mlx_put_pixel(p->img, x, y, pixel(&final, 255));

		}
	}
}
