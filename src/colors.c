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

t_color	add_light(t_color color, t_color light, float p2)
{
	t_color	c;

	if (p2 > 1)
		p2 = 1;
	if (p2 < 0)
		p2 = 0;
	c.r = color.r * light.r * p2;
	c.g = color.g * light.g * p2;
	c.b = color.b * light.b * p2;
	if (c.r > 1)
		c.r = 1;
	if (c.g > 1)
		c.g = 1;
	if (c.b > 1)
		c.b = 1;
	if (c.r < 0)
		c.r = 0;
	if (c.g < 0)
		c.g = 0;
	if (c.b < 0)
		c.b = 0;
	return (c);
}

t_color	ambient(t_color *color, t_ambient *a)
{
	t_color	ambient;

	ambient.r = color->r * (int32_t)(a->rgb.r * a->ratio) / 255;
	ambient.g = color->g * (int32_t)(a->rgb.g * a->ratio) / 255;
	ambient.b = color->b * (int32_t)(a->rgb.b * a->ratio) / 255;
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

t_color	diffuse(t_pixel pixel, t_ambient *a, t_light *light, t_coord light_dir)
{
	t_color diffuse;
	t_color	amb;
	double	i_diffuse;

	amb = ambient(&pixel.rgb, a);
	double cos = dot_product(pixel.normal, light_dir);
	//double cos = dot_product(pixel.normal, vector_scale(light_dir,-1));
	
	//i_diffuse = ambient->ratio;
	i_diffuse = light->brightness * cos;
	//diffuse = add_light(pixel.rgb, light->rgb, i_diffuse);
	//i_diffuse = 1;
	//printf("%f\n", i_diffuse);

	diffuse.r = pixel.rgb.r * (int32_t)(light->rgb.r * i_diffuse) / 255 + amb.r;
	diffuse.g = pixel.rgb.g * (int32_t)(light->rgb.g * i_diffuse) / 255 + amb.g;
	diffuse.b = pixel.rgb.b * (int32_t)(light->rgb.b * i_diffuse) / 255 + amb.b;
	// 
	//printf("%d\n", diffuse.r);
    // Clamp values to [0, 255]
     diffuse.r = fmin(255, fmax(0, diffuse.r));
     diffuse.g = fmin(255, fmax(0, diffuse.g));
     diffuse.b = fmin(255, fmax(0, diffuse.b));
	//diffuse = pixel.rgb;
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
