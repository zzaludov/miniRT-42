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

t_shader	ambient(t_color *color, t_ambient *a)
{
	t_shader	amb;

	amb.r = a->rgb.r / 255. * a->ratio * color->r / 255.;
	amb.g = a->rgb.r / 255. * a->ratio * color->g / 255.;
	amb.b = a->rgb.r / 255. * a->ratio * color->b / 255.;
	return (amb);
}

t_shader	diffuse(t_pixel pixel, t_ambient *a, t_light *l, t_coord light_dir)
{
	t_shader	diff;
	double		cos;

	diff = ambient(&pixel.rgb, a);
	cos = dot_product(pixel.normal, light_dir);
	if (cos < 0)
		cos = 0;
	else
	{
		diff.r += cos * l->brightness * l->rgb.r / 255. * pixel.rgb.r / 255.;
		diff.g += cos * l->brightness * l->rgb.g / 255. * pixel.rgb.g / 255.;
		diff.b += cos * l->brightness * l->rgb.b / 255. * pixel.rgb.b / 255.;
	}
	if (diff.r > 1)
		diff.r = 1;
	if (diff.g > 1)
		diff.g = 1;
	if (diff.b > 1)
		diff.b = 1;
	return (diff);
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
