/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 22:42:14 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:11 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

int		ft_raycasting(t_cub3d *cub3d)
{
	int x;

	x = 0;
	while (x < cub3d->map.w)
	{
		cub3d->player.camerax = 2 * x / (double)cub3d->map.w - 1;
		cub3d->player.raydirx = cub3d->player.dirx + cub3d->player.planex
			* cub3d->player.camerax;
		cub3d->player.raydiry = cub3d->player.diry + cub3d->player.planey
			* cub3d->player.camerax;
		cub3d->player.mapx = (int)cub3d->player.posx;
		cub3d->player.mapy = (int)cub3d->player.posy;
		cub3d->player.deltadistx = fabs(1 / cub3d->player.raydirx);
		cub3d->player.deltadisty = fabs(1 / cub3d->player.raydiry);
		cub3d->player.hit = 0;
		ft_raycasting_1(cub3d);
		ft_draw_ray(cub3d, x);
		x++;
	}
	ft_sprite(cub3d);
	(cub3d->data.arg == 3) ? ft_screenshot(cub3d) : 0;
	key_move(cub3d);
	mlx_put_image_to_window(cub3d->data.mlx,
		cub3d->data.win, cub3d->data.img, 0, 0);
	return (1);
}

void	ft_raycasting_1(t_cub3d *cub3d)
{
	if (cub3d->player.raydirx < 0)
	{
		cub3d->player.stepx = -1;
		cub3d->player.sidedistx = (cub3d->player.posx - cub3d->player.mapx)
			* cub3d->player.deltadistx;
	}
	else
	{
		cub3d->player.stepx = 1;
		cub3d->player.sidedistx = (cub3d->player.mapx
			+ 1.0 - cub3d->player.posx) * cub3d->player.deltadistx;
	}
	if (cub3d->player.raydiry < 0)
	{
		cub3d->player.stepy = -1;
		cub3d->player.sidedisty = (cub3d->player.posy - cub3d->player.mapy)
			* cub3d->player.deltadisty;
	}
	else
	{
		cub3d->player.stepy = 1;
		cub3d->player.sidedisty = (cub3d->player.mapy
			+ 1.0 - cub3d->player.posy) * cub3d->player.deltadisty;
	}
	ft_raycasting_2(cub3d);
}

void	ft_raycasting_2(t_cub3d *cub3d)
{
	while (cub3d->player.hit == 0)
	{
		if (cub3d->player.sidedistx < cub3d->player.sidedisty)
		{
			cub3d->player.sidedistx += cub3d->player.deltadistx;
			cub3d->player.mapx += cub3d->player.stepx;
			cub3d->player.side = 0;
		}
		else
		{
			cub3d->player.sidedisty += cub3d->player.deltadisty;
			cub3d->player.mapy += cub3d->player.stepy;
			cub3d->player.side = 1;
		}
		if (cub3d->map.memoria[cub3d->player.mapx][cub3d->player.mapy] == '1')
			cub3d->player.hit = 1;
	}
	ft_raycasting_3(cub3d);
}

void	ft_raycasting_3(t_cub3d *cub3d)
{
	if (cub3d->player.side == 0)
	{
		cub3d->player.perpwalldist = (cub3d->player.mapx - cub3d->player.posx +
			(1 - cub3d->player.stepx) / 2) / cub3d->player.raydirx;
	}
	else
	{
		cub3d->player.perpwalldist = (cub3d->player.mapy - cub3d->player.posy +
			(1 - cub3d->player.stepy) / 2) / cub3d->player.raydiry;
	}
	cub3d->player.line_h = (cub3d->map.h / cub3d->player.perpwalldist);
	cub3d->player.drawstart = -cub3d->player.line_h / 2 + cub3d->map.h / 2;
	cub3d->player.drawstart =
		(cub3d->player.drawstart < 0) ? 0 : cub3d->player.drawstart;
	cub3d->player.drawend = cub3d->player.line_h / 2 + cub3d->map.h / 2;
	cub3d->player.drawend = (cub3d->player.drawend >= cub3d->map.h)
		? cub3d->map.h - 1 : cub3d->player.drawend;
	ft_raycasting_4(cub3d);
}

void	ft_raycasting_4(t_cub3d *cub3d)
{
	cub3d->player.texnum =
		(int)cub3d->map.memoria[cub3d->player.mapx][cub3d->player.mapy];
	if (cub3d->player.side == 0)
	{
		cub3d->player.wallx = cub3d->player.posy + cub3d->player.perpwalldist
			* cub3d->player.raydiry;
	}
	else
	{
		cub3d->player.wallx = cub3d->player.posx + cub3d->player.perpwalldist
			* cub3d->player.raydirx;
	}
	cub3d->player.wallx -= floor((cub3d->player.wallx));
	cub3d->player.texx = (int)(cub3d->player.wallx
		* (double)cub3d->player.tex_w);
	if (cub3d->player.side == 0 && cub3d->player.raydirx > 0)
		cub3d->player.texx = cub3d->player.tex_w - cub3d->player.texx - 1;
	if (cub3d->player.side == 1 && cub3d->player.raydiry < 0)
		cub3d->player.texx = cub3d->player.tex_w - cub3d->player.texx - 1;
	cub3d->player.step = 1.0 * cub3d->player.tex_h / cub3d->player.line_h;
	cub3d->player.texpos = (cub3d->player.drawstart
		- cub3d->map.h / 2 + cub3d->player.line_h / 2) * cub3d->player.step;
}
