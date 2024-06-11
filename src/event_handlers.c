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
#include "MLX42/MLX42.h"


void	handle_esc(mlx_t* mlx)
{
	// MLX_NONNULL(mlx);
	// glfwSetWindowShouldClose(mlx->window, true);
	mlx_close_window(mlx);
}

// void	handle_mouse(mouse_key_t button,
// 	action_t action, modifier_key_t mods, void *data)
// {
// 	t_pointer_mlx	*p;

// 	p = data;
// 	return ;//TODO
// }


void	handle_keys(mlx_key_data_t keys, void *data)
{
	t_pointer_mlx	*p;

	p = data;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
		handle_esc(p->mlx);
	else if (keys.action != MLX_RELEASE && !keys.modifier
		&& (keys.key == MLX_KEY_A || keys.key == MLX_KEY_W
			|| keys.key == MLX_KEY_D || keys.key == MLX_KEY_S
			|| keys.key == MLX_KEY_PAGE_UP || keys.key == MLX_KEY_PAGE_DOWN
			|| keys.key == MLX_KEY_1 || keys.key == MLX_KEY_2))
		find_highlited(p, keys);
}

void handle_keys_wrapper(struct mlx_key_data keys, void *data)
{
    handle_keys(keys, (t_pointer_mlx *)data);
}