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
	mlx_close_window(mlx);
}

void	reset_highlight(t_pointer_mlx *p)
{
	int	i;

	i = -1;
	while (++i < p->scene->n_cy)
		if (p->scene->cy[i]->highlighted == 1)
			p->scene->cy[i]->highlighted = 0;
	i = -1;
	while (++i < p->scene->n_pl)
		if (p->scene->pl[i]->highlighted == 1)
			p->scene->pl[i]->highlighted = 0;
	i = -1;
	while (++i < p->scene->n_sp)
		if (p->scene->sp[i]->highlighted == 1)
			p->scene->sp[i]->highlighted = 0;
}

void	handle_mouse(mouse_key_t button,
	action_t action, modifier_key_t mods, void *data)
{
	t_pointer_mlx	*p;
	int32_t			x;
	int32_t			y;
	int				i;
	int static		switch_flag = 0;

	i = -1;
	p = data;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT
		&& (action != MLX_RELEASE && action != MLX_REPEAT))
	{
		mlx_get_mouse_pos(p->mlx, &x, &y);
		if (switch_flag == 1)
		{
			reset_highlight(p);
			switch_flag = 0;
		}
		if (p->pixel[x][y].object == 'c' || p->pixel[x][y].object == 'd')
		{
			p->scene->cy[p->pixel[x][y].index]->highlighted = 1;
			switch_flag = 1;
			write(1, "pointing on cy\n", 15);
		}
		if (p->pixel[x][y].object == 'p')
		{
				p->scene->pl[p->pixel[x][y].index]->highlighted = 1;
				switch_flag = 1;
				write(1, "pointing on pl\n", 15);
		}
		if (p->pixel[x][y].object == 's')
		{
				p->scene->sp[p->pixel[x][y].index]->highlighted = 1;
				switch_flag = 1;
				write(1, "pointing on sp\n", 15);
		}
	}
}

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
			|| keys.key == MLX_KEY_1 || keys.key == MLX_KEY_2
			|| keys.key == MLX_KEY_3 || keys.key == MLX_KEY_4))
		find_highlited(p, keys);
}

void handle_keys_wrapper(struct mlx_key_data keys, void *data)
{
    handle_keys(keys, (t_pointer_mlx *)data);
}

