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

void	hooks(t_pointer_mlx p, mlx_t *mlx)
{
	pixel_struct(&p);
	//open_map(&p);
	mlx_loop_hook(mlx, pixeling, &p);
	//mlx_key_hook(mlx, &handle_keys_wrapper, &p);
	//mlx_mouse_hook(mlx, &handle_mouse, &p);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	final_free(&p);
	free(p.map_name);
}

int32_t	main(int argc, char **argv)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_pointer_mlx	p;

	(void) argc;
	if (argc == 2)
	{
		p.map_name = validate_name(argv[1]);
		validate_map(p.map_name, &p);
		mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
		if (!mlx)
			return (1);
		img = mlx_new_image(mlx, WIDTH, HEIGHT);
		if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
			return (1);
		p.mlx = mlx;
		p.img = img;
		hooks(p, mlx);
	}
	else
		ft_putendl_fd("Enter valid arguments: [./miniRT] [scene_name.rt]", 2);
	return (MLX_SUCCESS);
}
