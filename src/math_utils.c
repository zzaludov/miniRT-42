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

int	discriminant(t_discriminant d, double *t, int *inside)
{
	double	discriminant;
	double	x1;
	double	x2;

	*inside = 0;
	discriminant = d.b * d.b - 4 * d.a * d.c;
	if (discriminant < 0)
		return (0);
	else if (discriminant == 0)
		*t = -d.b / (2.0 * d.a);
	else
	{
		x1 = (-d.b - sqrt(discriminant)) / (2.0 * d.a);
		x2 = (-d.b + sqrt(discriminant)) / (2.0 * d.a);
		if (x1 < 0 && x2 < 0)
			return (0);
		else if (x2 < 0 || (x1 < x2 && x1 > 0))
			*t = x1;
		else if (x1 < 0 || x1 > x2)
			*t = x2;
		if ((x2 < 0 && x1 > 0) || (x2 > 0 && x1 < 0))
			*inside = 1;
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

t_coord	transformation_matrix(t_coord cam_dir, t_coord ray_dir)
{
	t_coord	up;
	t_coord	right;
	t_coord	forward;
	t_coord	transform;

	up = create_vector(0, 1, 0);
	forward = normalized(cam_dir);
	right = cross_product(up, forward);
	up = cross_product(forward, right);
	transform.x = ray_dir.x * right.x
		+ ray_dir.y * up.x + ray_dir.z * forward.x;
	transform.y = ray_dir.x * right.y
		+ ray_dir.y * up.y + ray_dir.z * forward.y;
	transform.z = ray_dir.x * right.z
		+ ray_dir.y * up.z + ray_dir.z * forward.z;
	return (transform);
}
