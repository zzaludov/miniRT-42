/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:08:16 by zzaludov          #+#    #+#             */
/*   Updated: 2024/06/27 19:10:58 by nandroso         ###   ########.fr       */
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
# define EPSILON 1e-4
# define WIDTH 1000
# define HEIGHT 600

typedef struct s_vec3f
{
	double	x;
	double	y;
	double	z;
}	t_vec3f;

typedef struct s_quat4f
{
	t_vec3f	xyz;
	float	w;
}	t_quat4f;

// attributes structures
typedef struct s_shader
{
	float	r;
	float	g;
	float	b;
}	t_shader;

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

typedef struct s_discriminant
{
	double	a;
	double	b;
	double	c;
}	t_discriminant;

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
	double	brightness;
	t_color	rgb;
}	t_light;

// objects structures
typedef struct s_sphere
{
	t_coord	pos;
	double	diameter;
	t_color	rgb;
	int		highlighted;
	int		inside;
}	t_sphere;

typedef struct s_plane
{
	t_coord	pos;
	t_coord	dir;
	t_color	rgb;
	int		highlighted;
}	t_plane;

typedef struct s_cylinder
{
	t_coord	pos;
	t_coord	dir;
	double	diameter;
	double	height;
	t_color	rgb;
	int		highlighted;
	int		inside;
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

typedef struct s_pixel
{
	t_color			rgb;
	double			cam_dist;
	double			light_dist;
	char			object;
	int				index;
	int				inside;
	t_coord			normal;
	t_coord			intersection;
}	t_pixel;

typedef struct s_pointer_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	char			*map_name;
	t_scene			*scene;
	t_pixel			**pixel;

}	t_pointer_mlx;

//parse_map.c
void		open_map(t_pointer_mlx *p);
void		pixel_struct(t_pointer_mlx	*p);
t_scene		*init_scene(char *file);
void		final_free(t_pointer_mlx *p);
void		validate_ambient(char **spl);
void		validate_xyz(char **spl, char flag);
// main_utils
char		*validate_name(char *scene_name);
void		validate_map(char *map_name, t_pointer_mlx *p);
t_coord		split_xyz(char *str, char flag);
t_color		split_rgb(char *str);
// error_handling
void		print_to_exit(char *msg);
// colors
void		pixeling(void *p);
int32_t		pixel(t_color *color, int32_t a);
t_shader	ambient(t_color *color, t_ambient *a);
t_shader	diffuse(t_pixel p, t_ambient *a, t_light *l, t_coord light_dir);
void		alpha_screen(mlx_image_t *img);
//intersection
void		find_intersection(t_pointer_mlx *p,
				t_pixel *pixel, t_coord ray_dir);
int			find_shadow(t_pointer_mlx *p,
				t_pixel *pixel, t_coord light_dir);
int			intersect_pl(t_coord ray_org,
				t_coord ray_dir, t_plane *pl, double *t);
int			intersect_sp(t_coord ray_org,
				t_coord ray_dir, t_sphere *sp, double *t);
int			intersect_cy(t_coord ray_org,
				t_coord ray_dir, t_cylinder *cy, double *t);
int			intersect_disk(t_coord ray_org,
				t_coord ray_dir, t_cylinder *cy, double *t);
//vectors
t_coord		create_vector(double x, double y, double z);
t_coord		vector_scale(t_coord v, double sc);
t_coord		normalized(t_coord v);
t_coord		vector_add(t_coord v1, t_coord v2);
t_coord		vector_subtract(t_coord v1, t_coord v2);
t_coord		vector_multiply(t_coord v1, t_coord v2);
t_coord		cross_product(t_coord v1, t_coord v2);
t_coord		vector_projection(t_coord v1, t_coord v2);
double		vector_len(t_coord v);
double		dot_product(t_coord v1, t_coord v2);
// math utils
double		deg_to_rad(double deg);
t_coord		transformation_matrix(t_coord cam_dir, t_coord ray_dir);
int			discriminant(t_discriminant d, double *t, int *inside);
t_quat4f	ft_quat4f_conjugate(t_quat4f q);
t_quat4f	ft_quat4f_prod(t_quat4f const q, t_quat4f const p);
t_quat4f	ft_quat4f_unit(t_quat4f const q);
float		ft_vec3f_dot(t_vec3f const u, t_vec3f const v);
t_vec3f		ft_vec3f_prod(t_vec3f const u, float const t);
t_vec3f		ft_vec3f(float const x, float const y, float const z);
t_quat4f	ft_quat4f(t_vec3f const xyz, float const w);
// utils
int			arrlen(char **array);
void		free_memory(void **ptr);
bool		compare(const char *s1, const char *s2, size_t n);
double		ft_atof(const char *nptr);
void		handle_esc(t_pointer_mlx *p);
//object manipulation
void		sphere_manipulation(t_scene *scene, t_sphere *sphere,
				mlx_key_data_t keys);
void		plane_manipulation(t_scene *scene, t_plane *plane,
				mlx_key_data_t keys);
void		cylinder_manipulation(t_scene *scene, t_cylinder *cylinder,
				mlx_key_data_t keys);
void		mutate_diameter(double *diameter, keys_t key);
void		mutate_pos( t_camera *camera, t_coord *pos, keys_t key);
void		mutate_height(double *height, keys_t key);
void		find_highlited(t_pointer_mlx *p, mlx_key_data_t keys);
void		handle_keys(mlx_key_data_t keys, void *data);
void		handle_mouse(mouse_key_t button, action_t action,
				modifier_key_t mods, void *data);
void		handle_keys_wrapper(struct mlx_key_data keys, void *data);
void		rotate_plane(mlx_key_data_t keys, t_plane *plane);
void		rotate_cylinder(mlx_key_data_t keys, t_cylinder *cylinder);
void		rotate_camera(mlx_key_data_t keys, t_camera *camera);
void		pos_right(t_camera *camera, t_coord *pos);
void		pos_left(t_camera *camera, t_coord *pos);
void		pos_straight(t_camera *camera, t_coord *pos);
void		pos_back(t_camera *camera, t_coord *pos);
void		pos_up(t_camera *camera, t_coord *pos);
void		pos_down(t_camera *camera, t_coord *pos);
void		move_light(mlx_key_data_t keys, void *data);
void		move_camera(mlx_key_data_t keys, t_camera *camera);

#endif
