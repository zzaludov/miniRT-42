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
t_coord	creating_ray(int pixel_x, int pixel_y, double fov, t_coord cam_dir)
{
	t_coord	ray_dir;
	double	width;
	double	height;
	double	fov_to_height;

	width = (double)WIDTH;
	height = (double)HEIGHT;
	fov_to_height = tan(deg_to_rad(fov * 0.5));
	ray_dir.x = fov_to_height * (width / height) * (2.0 * (pixel_x + 0.5) / width - 1.0);
	ray_dir.y = fov_to_height * (1.0 - 2.0 * (pixel_y + 0.5) / height);
	ray_dir.z = -1.0;
	ray_dir = transformation_matrix(cam_dir, ray_dir);
	ray_dir = normalized(ray_dir);
	return (ray_dir);
}

void	calculate_normal(t_scene *s, t_pixel *pixel)
{
	 t_coord	cp;
	 double	projection_lenght;

	if(pixel->object == 's')
		pixel->normal = normalized(vector_subtract(pixel->intersection, s->sp[pixel->index]->pos));
	else if(pixel->object == 'c')
	{
		s->cy[pixel->index]->dir = normalized(s->cy[pixel->index]->dir);
		cp = vector_subtract(pixel->intersection, s->cy[pixel->index]->pos);
		projection_lenght = dot_product(s->cy[pixel->index]->dir, cp);
		pixel->normal =vector_subtract(pixel->intersection, vector_scale(s->cy[pixel->index]->dir, projection_lenght));
		pixel->normal = normalized(vector_subtract(pixel->normal, s->cy[pixel->index]->pos));
	}
	else if(pixel->object == 'd')
		pixel->normal = s->cy[pixel->index]->dir;
	else if(pixel->object == 'p')
		pixel->normal = s->pl[pixel->index]->dir;
	// if ((pixel->object == 'd' || pixel->object == 'c') && s->cy[pixel->index]->inside)
	// 	pixel->normal = vector_scale(pixel->normal, -1);
	// if (pixel->object == 's' && s->sp[pixel->index]->inside)
	// 	pixel->normal = vector_scale(pixel->normal, -1);
}

t_shader	pixel_shader(t_pointer_mlx *p, int x, int y)
{
	t_coord		ray_dir;
	t_coord		light_dir;
	t_shader	shader;

	ray_dir = creating_ray(x, y, p->scene->c->fov, p->scene->c->dir);
	find_intersection(p, &p->pixel[x][y], ray_dir);
	p->pixel[x][y].intersection = vector_scale(ray_dir, p->pixel[x][y].cam_dist);
	p->pixel[x][y].intersection = vector_add(p->pixel[x][y].intersection, p->scene->c->pos);
	calculate_normal(p->scene, &p->pixel[x][y]);
	light_dir = vector_subtract(p->scene->l->pos, p->pixel[x][y].intersection);	
	p->pixel[x][y].light_dist = vector_len(light_dir);
	light_dir = normalized(light_dir);
	if (p->pixel[x][y].index != -1 && find_shadow(p, &p->pixel[x][y], light_dir))
		shader = diffuse(p->pixel[x][y], p->scene->a, p->scene->l, light_dir);
	else
		shader = ambient(&p->pixel[x][y].rgb, p->scene->a);
	return (shader);
}

// https://brilliant.org/wiki/3d-coordinate-geometry-equation-of-a-line/

void	pixeling(void *param)
{
	t_pointer_mlx *p;
	t_color			final;
	t_shader		shader;
	int				i;

	p = param;
	i = 0;
	while (i < WIDTH)
		free(p->pixel[i++]);
	free(p->pixel);
	pixel_struct(p);
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {	
			shader = pixel_shader(p, x, y);
			final.r = shader.r * 255;
			final.g = shader.g * 255;
			final.b = shader.b * 255;
			mlx_put_pixel(p->img, x, y, pixel(&final, 255));
		}
	}
}
