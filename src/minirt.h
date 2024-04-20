/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:08:16 by zzaludov          #+#    #+#             */
/*   Updated: 2023/11/27 20:08:42 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../FT_LIBRARY/ft_library.h"
# define EPSILON 1e-6
# define WIDTH 1000
# define HEIGHT 600

// attributes structures
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

//4D vector structure 
typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
	double		w;
}	t_vector;

// elements structures
typedef struct s_ambient
{
	double	ratio;
	t_color	rgb;
}	t_ambient;

typedef struct s_camera
{
	t_coord	pos;
	t_coord	dir;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_coord	pos;
	float	brightness;
	t_color	rgb;
}	t_light;

// objects structures
typedef struct s_sphere
{
	t_coord	pos;
	double	diameter;
	t_color	rgb;
}	t_sphere;

typedef struct s_plane
{
	t_coord	pos;
	t_coord	dir;
	t_color	rgb;
}	t_plane;

typedef struct s_cylinder
{
	t_coord	pos;
	t_coord	dir;
	double	diameter;
	double	height;
	t_color	rgb;
}	t_cylinder;

// main info about scene structures
typedef struct s_scene
{
	t_ambient	*a;
	t_camera	*c;
	t_light		*l;
	t_sphere	**sp;
	t_plane		**pl;
	t_cylinder	**cy;
	int			n_sp;
	int			n_pl;
	int			n_cy;
}	t_scene;

typedef struct s_pointer_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			*map_name;
	t_scene			*scene;
	t_color			**pixel_rgb;
	//int32_t			**pixel_rgb;   //save color of pixel of x and y axis: pixel[x][y]
	double			**pixel_dist;  //distance of saved color for comparison
}	t_pointer_mlx;

//parse_map.c
void		open_map(t_pointer_mlx *p);
t_scene		*init_scene(char* file);

// utils.c
int			discriminant(double a, double b, double c, double *t);
int			arrlen(char **array);
void		free_memory(void **ptr);
bool		compare(const char *s1, const char *s2, size_t n);
double		ft_atof(const char *nptr);

int32_t		pixel(t_color *color, int32_t a);
int32_t		ambient(t_color *color, t_ambient *a);
int32_t		light(t_color *color, t_light *l);
//int32_t		pixel(int32_t r, int32_t g, int32_t b, int32_t a);

void 		pixeling(t_pointer_mlx *p);

int			intersect_plane(t_coord ray_org, t_coord ray_dir, t_plane *plane, double *t);
int			intersect_sphere(t_coord ray_org, t_coord ray_dir, t_sphere *sp, double *t);
int 		intersect_cylinder(t_coord ray_org, t_coord ray_dir, t_cylinder *cy, double *t);
int			intersect_disk(t_coord ray_org, t_coord ray_dir, t_cylinder* cy, double* t);

//vectors
t_coord		create_vector(double x, double y, double z);
t_coord		vector_scale(t_coord v, double sc);
t_coord		normalized(t_coord v);
t_coord		vector_add(t_coord v1, t_coord v2);
t_coord		vector_subtract(t_coord v1, t_coord v2);
t_coord		vector_produkt(t_coord v1, t_coord v2);
t_coord		vector_projection(t_coord v1, t_coord v2);
double		vector_len(t_coord v);
double		vector_point(t_coord v1, t_coord v2);
double		deg_to_rad(double deg);

#endif
