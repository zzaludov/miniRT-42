/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzaludov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:33:00 by zzaludov          #+#    #+#             */
/*   Updated: 2023/11/27 19:33:15 by zzaludov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*validate_name(char *scene_name)
{
	if (access(scene_name, F_OK) == -1
		|| !ft_strnstr(scene_name, ".rt", ft_strlen(scene_name)))
	{
		ft_putendl_fd
			("Error!\nIncorrect format of unexisting configuration file", 2);
		exit(1);
	}
	else
		return (ft_strdup(scene_name));
}