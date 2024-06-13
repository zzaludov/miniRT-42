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
//int32_t	ambient(t_color *color, t_ambient *a)
{
	t_color	ambient;

//	ambient.r = (color.r + color2.r > 255) ? 255 : color.r + color2.r;
//	ambient.g = (color.g + color2.g > 255) ? 255 : color.g + color2.g;
//	ambient.b = (color.b + color2.b > 255) ? 255 : color.b + color2.b;
	ambient.r = (color->r * (int32_t)(a->rgb.r * a->ratio)) / 255;
	ambient.g = (color->g * (int32_t)(a->rgb.g * a->ratio)) / 255;
	ambient.b = (color->b * (int32_t)(a->rgb.b * a->ratio)) / 255;
	//return (pixel(&ambient, 255));  //?
	return (ambient);
	
}

t_color	light(t_color *color, t_light *l)
//int32_t	light(t_color *color, t_light *l)
{
	t_color	light;

//	ambient.r = (color.r + color2.r > 255) ? 255 : color.r + color2.r;
//	ambient.g = (color.g + color2.g > 255) ? 255 : color.g + color2.g;
//	ambient.b = (color.b + color2.b > 255) ? 255 : color.b + color2.b;
	light.r = (color->r * (int32_t)(l->rgb.r * l->brightness)) / 255;
	light.g = (color->g * (int32_t)(l->rgb.g * l->brightness)) / 255;
	light.b = (color->b * (int32_t)(l->rgb.b * l->brightness)) / 255;
	//return (pixel(&light, 255));
	return (light);
}

t_color	diffuse(t_pixel pixel, t_ambient *ambient, t_light *light, t_coord light_dir)
{
	t_color diffuse;
	double a = 1.0;  // Constant attenuation coefficient
    double b = 0.1;  // Linear attenuation coefficient
    double c = 0.01; // Quadratic attenuation coefficient

	double	i_ambient;
	double	i_diffuse;
	//double	intensity;
	double	attenuation_coefficients;

	i_ambient = Ka * ambient->ratio;
	i_diffuse = Kd * light->brightness * vector_point(light_dir, pixel.intersection);

	attenuation_coefficients = (a + b * pixel.light_dist + c * pow(pixel.light_dist, 2));
	//intensity = (i_ambient * i_diffuse) / attenuation_coefficients;

	diffuse.r = (int)(pixel.rgb.r * i_ambient + light->rgb.r * i_diffuse / attenuation_coefficients);
    diffuse.g = (int)(pixel.rgb.g * i_ambient + light->rgb.g * i_diffuse / attenuation_coefficients);
    diffuse.b = (int)(pixel.rgb.b * i_ambient + light->rgb.b * i_diffuse / attenuation_coefficients);

    // Clamp values to [0, 255]
    diffuse.r = fmin(255, diffuse.r);
    diffuse.g = fmin(255, diffuse.g);
    diffuse.b = fmin(255, diffuse.b);

	return (diffuse);
}

void	alpha_screen(mlx_image_t *img)
{
	int	x;
	int	y;
 
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(img, x, y, 0xFFFFFF00);
			x++;
		}
		y++;
	}
}
