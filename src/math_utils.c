/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:48:30 by zzaludov          #+#    #+#             */
/*   Updated: 2024/04/25 21:48:32 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	deg_to_rad(double deg)
{
	return (deg * 3.141529 / 180.0);
}

int	discriminant(double a, double b, double c, double *t)
{
	double	discriminant;
	double	x1;
	double	x2;

	discriminant = b * b - 4 * a * c; // +c

	if (discriminant < 0)
		return (0);
	else if (discriminant == 0)
		*t = -b / (2.0 * a);
	else
	{
		x1 = (-b - sqrt(discriminant)) / (2.0 * a);
		x2 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (x1 < 0 && x2 < 0)
			return (0);
		else if (x2 < 0 || x1 < x2)
			*t = x1;
		else if (x1 < 0 || x1 > x2)
			*t = x2;
	}
	return (1);
}

// 1.calculate CAMERA-TO-WORLD MATRIX

// | R11  R12  R13  Tx |
// | R21  R22  R23  Ty |
// | R31  R32  R33  Tz |
// |  0    0    0    1 |

// T represents position of the camera
// R represents rotation matrix

// ROTATION MATRIX

// | Right_x   Right_y   Right_z   |
// | Up_x      Up_y      Up_z      |
// | Forward_x Forward_y Forward_z |

// Right = Up * Forward
// Up = (0, 1, 0)
// Forward = normalized orientation vector (dir)

// 1.calculate WORLD-TO-CAMERA MATRIX (inverse matrix)
/*
t_coord	transformation_matrix(t_coord pos, t_coord dir)
{
	t_coord	up;
	t_coord right;
	t_coord	trans;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	right = vector_produkt(up, dir);
	
}*/
