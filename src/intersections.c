/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:35:57 by zzaludov          #+#    #+#             */
/*   Updated: 2023/12/06 21:36:00 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// Parametric form of RAY
// ray_org + ray_dir * t

// intersection point position:
// t = ((pl->pos - ray_org) * pl->dir) / ray_dir * pl->dir
int	intersect_plane(t_coord ray_org, t_coord ray_dir, t_plane *plane, double *t)
{
	double	denominator;

	denominator = vector_point(plane->dir, ray_dir);
	if (fabs(denominator) < EPSILON)
	{
		return 0; // Ray is parallel to the plane, no intersection
	}
	*t = vector_point(vector_subtract(plane->pos, ray_org), plane->dir) / denominator;
	if (*t < 0)
	{
		return 0;
	}
	return 1;
}

// a = dot (ray_dir, ray_dir)
// b = 2 * dot (ray_org - sp->pos, ray_dir);
// c = dot (ray_org - sp->pos, ray_org - sp->pos) - sqrt(r)
int	intersect_sphere(t_coord ray_org, t_coord ray_dir, t_sphere *sp, double *t)
{
	t_coord	vector;
	double	a;
	double	b;
	double	c;
	//double	r;

	vector = vector_subtract(ray_org, sp->pos);
	//r = sp->diameter / 2;

	a = vector_point(ray_dir, ray_dir);
	b = 2.0 * vector_point(vector, ray_dir);
	c = vector_point(vector, vector) - sp->diameter * sp->diameter;
	//c = vector_point(vector, vector) - sqrt(r);
	return (discriminant(a, b, c, t));
}

// intersection point:
// p = ray_org + ray_dir * t
// vector from disk center to intersection point:
// v = pl.dir - pl.org
// sqrt distance from disk center to intersection
// d2 = dot(v, v)
// distance comparason
// d2 <= r * r
int intersect_disk(t_coord ray_org, t_coord ray_dir, t_cylinder* cy, double* t)
{
	t_plane	pl;
	t_coord	v;
	t_coord	p;

	pl.dir = cy->dir;  // is this correct?
	pl.rgb = cy->rgb;
	pl.pos = cy->pos;
	if (intersect_plane(ray_org, ray_dir, &pl, t))  // maybe not use same t?
	{
		p = vector_add(ray_org, vector_scale(ray_dir, *t));
		v = vector_add(p, vector_scale(pl.pos, -1));
		// v = vector_subtract(pl.dir, pl.org);
		if (sqrt(vector_point(v, v)) <= cy->diameter / 2.0)
			return 1;
	}

	pl.pos = vector_add(cy->pos, vector_scale(cy->dir, cy->height));
	if (intersect_plane(ray_org, ray_dir, &pl, t))
	{
		p = vector_add(ray_org, vector_scale(ray_dir, *t));
		v = vector_add(p, vector_scale(pl.pos, -1));
		if (sqrt(vector_point(v, v)) <= cy->diameter / 2.0)
		//if (sqrt(vector_point(v, v)) <= sqrt(cy->diameter / 2.0))
			return 1;
	}
	return 0;
}

int intersect_cylinder(t_coord ray_org, t_coord ray_dir, t_cylinder *cy, double *t)
{
	t_coord	vector;
	double	a;
	double	b;
	double	c;
	
	vector = vector_subtract(ray_org, cy->pos);

	a = vector_point(ray_dir, ray_dir) - pow(vector_point(ray_dir, cy->dir), 2);
	b = 2.0 * (vector_point(vector, ray_dir) - vector_point(vector, cy->dir)
	* vector_point(ray_dir, cy->dir));
	c = vector_point(vector, vector) - pow(vector_point(vector, cy->dir), 2)
	- pow(cy->diameter / 2.0, 2);

	if (!discriminant(a, b, c, t))
		return 0;

	// Calculate intersection point
	t_coord intersection_point = vector_add(ray_org, vector_scale(ray_dir, *t));

	// Check if intersection point is within the height bounds of the cylinder
	t_coord v = vector_subtract(intersection_point, cy->pos);
	double projection = vector_point(v, cy->dir);
	if (projection < 0 || projection > cy->height)
		return 0; // Intersection is outside the height bounds of the cylinder
	//cap	
/*	double distance_to_axis_squared = vector_point(v, v) - pow(projection, 2);
	if (distance_to_axis_squared > pow(cy->diameter / 2.0, 2))
		return 0; */

	return 1;

}
