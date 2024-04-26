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

int	discriminant(double a, double b, double c, double *t)
{
	double	discriminant;
	double	x1;
	double	x2;

	discriminant = b * b - 4 * a * c;

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
		else if (b < 0)  // (x2 < 0 || x1 < x2) 
			*t = x1;
		else             // (x1 < 0 || x1 > x2) 
			*t = x2;
	}
	return (1);
}

// CAMERA-TO-WORLD MATRIX

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
// Forward = normalized orientation vector
/*
t_coord	transformation_matrix(t_coord pos, t_coord dir)
{
	t_coord	up;
	t_coord forward;
	t_coord	trans;

	up.x = 0;
	up.y = 1;
	up.z = 0;
	forward = vector_produkt(up, dir);
	
}*/
