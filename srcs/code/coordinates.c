/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:05:42 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:47 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void		ft_no_so(t_cub3d *cub3d)
{
	if (cub3d->player.nswe == 'N')
	{
		cub3d->player.dirx = -1;
		cub3d->player.diry = 0.0;
		cub3d->player.planex = 0.0;
		cub3d->player.planey = 0.66;
	}
	else if (cub3d->player.nswe == 'S')
	{
		cub3d->player.dirx = 1;
		cub3d->player.diry = 0.0;
		cub3d->player.planex = 0.0;
		cub3d->player.planey = -0.66;
	}
	else if ((cub3d->player.nswe == 'W') || (cub3d->player.nswe == 'E'))
		ft_we_ea(cub3d);
}

void		ft_we_ea(t_cub3d *cub3d)
{
	if (cub3d->player.nswe == 'W')
	{
		cub3d->player.dirx = 0.0;
		cub3d->player.diry = -1;
		cub3d->player.planex = -0.66;
		cub3d->player.planey = 0.0;
	}
	else if (cub3d->player.nswe == 'E')
	{
		cub3d->player.dirx = 0.0;
		cub3d->player.diry = 1;
		cub3d->player.planex = 0.66;
		cub3d->player.planey = 0.0;
	}
}
