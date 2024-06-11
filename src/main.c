/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:33:00 by zzaludov          #+#    #+#             */
/*   Updated: 2023/11/27 19:33:15 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_objs(char *file, char *obj)
{
	int		objs;
	int		fd;
	char	*line;
	char	*found;

	objs = 0;
	fd = open(file, 0);
	if (fd == -1)
		ft_printf("Opening file failure."); // error
	line = get_next_line(fd);
	while (line != NULL)
	{
		found = ft_strnstr(line, obj, ft_strlen(obj));
		if (found != NULL)
			objs++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (objs);
}

t_scene	*init_scene(char *file)
{
	t_scene	*scene;

	if (find_objs(file, "A") != 1 || find_objs(file, "C") != 1
		|| find_objs(file, "L") != 1)
		ft_printf("Element missing"); // error, call it differently than element
	scene = malloc (sizeof(t_scene));
	scene->a = malloc (sizeof(t_ambient));
	scene->c = malloc (sizeof(t_camera));
	scene->l = malloc (sizeof(t_light));
	scene->sp = malloc ((find_objs(file, "sp") + 1) * sizeof(t_sphere *));
	scene->pl = malloc ((find_objs(file, "pl") + 1) * sizeof(t_plane *));
	scene->cy = malloc ((find_objs(file, "cy") + 1) * sizeof(t_cylinder *));
	scene->n_sp = 0;
	scene->n_pl = 0;
	scene->n_cy = 0;
	return (scene);
}

void	final_free(t_pointer_mlx *p)
{
	int	i;

	free(p->scene->a);
	free(p->scene->c);
	free(p->scene->l);
	i = 0;
	while (p->scene->sp[i] != NULL)
		free(p->scene->sp[i++]);
	free(p->scene->sp);
	i = 0;
	while (p->scene->pl[i] != NULL)
		free(p->scene->pl[i++]);
	free(p->scene->pl);
	i = 0;
	while (p->scene->cy[i] != NULL)
		free(p->scene->cy[i++]);
	free(p->scene->cy);
	free(p->scene);
	i = 0;
	while (i < WIDTH)
		free(p->pixel[i++]);
	free(p->pixel);
}

void	read_map(t_pointer_mlx	*p)
//void	read_map_hook(void *param)
{
	//t_pointer_mlx	*p;
	int				i;
	int				j;

	i = 0;
	//p = param;
	p->scene = init_scene(p->map_name);
	
	p->pixel = (t_pixel **) malloc (WIDTH * sizeof(t_pixel *));
	while (i < WIDTH)
	{
		j = 0;
		p->pixel[i] = (t_pixel *) malloc (HEIGHT * sizeof(t_pixel));
		while (j < HEIGHT)
		{
			p->pixel[i][j].rgb.r = -1;
			p->pixel[i][j].rgb.g = -1;
			p->pixel[i][j].rgb.b = -1;
			p->pixel[i][j].cam_dist = -1; //?
			p->pixel[i][j].light_dist = -1; //?
			p->pixel[i][j].object = 0;  //?
			p->pixel[i][j].index = -1; //?
			j++;
		}
		i++;
	}
	open_map(p);
	//pixeling(p);
	//final_free(p);
}

int32_t	main(int argc, char **argv)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_pointer_mlx	p;

	(void) argc;
	if (argc == 2)
	{
		// p.map_name = ft_strdup(argv[1]);
		p.map_name = validate_name(argv[1]);
		validate_map(p.map_name);
		mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
		if (!mlx)
			return (1);
		img = mlx_new_image(mlx, WIDTH, HEIGHT);
		if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
			return (1);
		p.mlx = mlx;
		p.img = img;

		read_map(&p);
		mlx_loop_hook(mlx, pixeling, &p);
		//mlx_loop_hook(mlx, read_map_hook, &p);
		mlx_key_hook(mlx, &handle_keys_wrapper, &p);
		// mlx_mouse_hook(mlx, &handle_mouse, &p);
		mlx_loop(mlx);
		mlx_terminate(mlx);
		final_free(&p);
		free(p.map_name);
	}
	else
		ft_putendl_fd("Enter valid arguments: [./miniRT] [scene_name.rt]", 2);
	return (MLX_SUCCESS);
}
