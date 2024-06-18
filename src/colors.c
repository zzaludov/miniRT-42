/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:30:04 by zzaludov          #+#    #+#             */
/*   Updated: 2023/12/02 21:30:14 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/* 
int32_t	pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}*/

int32_t	pixel(t_color *color, int32_t a)
{
	return (color->r << 24 | color->g << 16 | color->b << 8 | a);
}

t_color	ambient(t_color *color, t_ambient *a)
{
	t_color	ambient;

	ambient.r = (color->r * (int32_t)(a->rgb.r * a->ratio)) / 255;
	ambient.g = (color->g * (int32_t)(a->rgb.g * a->ratio)) / 255;
	ambient.b = (color->b * (int32_t)(a->rgb.b * a->ratio)) / 255;
	// ambient.r = fmin(255, ambient.r);
    // ambient.g = fmin(255, ambient.g);
    // ambient.b = fmin(255, ambient.b);
	return (ambient);
}

t_color	light(t_color *color, t_light *l)
{
	t_color	light;

	light.r = (color->r * (int32_t)(l->rgb.r * l->brightness)) / 255;
	light.g = (color->g * (int32_t)(l->rgb.g * l->brightness)) / 255;
	light.b = (color->b * (int32_t)(l->rgb.b * l->brightness)) / 255;
	return (light);
}

t_color	diffuse(t_pixel pixel, t_ambient *ambient, t_light *light, t_coord light_dir)
{
	t_color diffuse;
	double	i_diffuse;
	double dot_product = vector_point(pixel.normal, light_dir);
	
	i_diffuse = ambient->ratio;
	i_diffuse = light->brightness * dot_product;
	//i_diffuse = 1;
	//printf("%f\n", i_diffuse);

	diffuse.r = (pixel.rgb.r * (int32_t)(light->rgb.r * i_diffuse)) / 255;
	diffuse.g = (pixel.rgb.g * (int32_t)(light->rgb.g * i_diffuse)) / 255;
	diffuse.b = (pixel.rgb.b * (int32_t)(light->rgb.b * i_diffuse)) / 255;
	printf("%d\n", diffuse.r);
    // Clamp values to [0, 255]
    // diffuse.r = fmin(255, fmax(0, diffuse.r));
    // diffuse.g = fmin(255, fmax(0, diffuse.g));
    // diffuse.b = fmin(255, fmax(0, diffuse.b));

	return (diffuse);
}

void	alpha_screen(mlx_image_t *img)
{
	int	x;
	int	y;
 
	y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			mlx_put_pixel(img, x, y, 0xFFFFFF00);
			x++;
		}
		y++;
	}
}
