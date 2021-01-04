/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 11:17:29 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:00 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void	ft_sprite(t_cub3d *cub3d)
{
	int		i;

	i = 0;
	while (++i < cub3d->sprite.num)
	{
		cub3d->sprite.order[i] = i;
		cub3d->xysp[i].rel = ((cub3d->player.posy - cub3d->xysp[i].y)
			* (cub3d->player.posy - cub3d->xysp[i].y) + (cub3d->player.posx
			- cub3d->xysp[i].x) * (cub3d->player.posx - cub3d->xysp[i].x));
	}
	ft_sort_sprites(cub3d);
	ft_ray_sprite(cub3d);
}

void	ft_ray_sprite(t_cub3d *cub3d)
{
	int i;

	i = 0;
	while (++i < cub3d->sprite.num)
	{
		cub3d->sprite.x =
			cub3d->xysp[cub3d->sprite.order[i]].x - cub3d->player.posx;
		cub3d->sprite.y =
			cub3d->xysp[cub3d->sprite.order[i]].y - cub3d->player.posy;
		cub3d->sprite.inv_det = 1.0 / (cub3d->player.planex
			* cub3d->player.diry - cub3d->player.dirx * cub3d->player.planey);
		cub3d->sprite.transform_x = cub3d->sprite.inv_det
			* (cub3d->player.diry * cub3d->sprite.x -
				cub3d->player.dirx * cub3d->sprite.y);
		cub3d->sprite.transform_y = cub3d->sprite.inv_det
			* (-cub3d->player.planey * cub3d->sprite.x +
				cub3d->player.planex * cub3d->sprite.y);
		cub3d->sprite.sprite_screen_x = (int)(cub3d->map.w / 2)
			* (1 + cub3d->sprite.transform_x / cub3d->sprite.transform_y);
		cub3d->sprite.sprite_h =
			abs((int)(cub3d->map.h / cub3d->sprite.transform_y));
		cub3d->sprite.drawstart_y =
			-cub3d->sprite.sprite_h / 2 + cub3d->map.h / 2;
		ft_ray_sprite_2(cub3d);
	}
}

void	ft_ray_sprite_2(t_cub3d *cub3d)
{
	if (cub3d->sprite.drawstart_y < 0)
		cub3d->sprite.drawstart_y = 0;
	cub3d->sprite.drawend_y =
			cub3d->sprite.sprite_h / 2 + cub3d->map.h / 2;
	if (cub3d->sprite.drawend_y >= cub3d->map.h)
		cub3d->sprite.drawend_y = cub3d->map.h - 1;
	cub3d->sprite.sprite_w =
		abs((int)(cub3d->map.h / cub3d->sprite.transform_y));
	cub3d->sprite.drawstart_x =
			-cub3d->sprite.sprite_w / 2 + cub3d->sprite.sprite_screen_x;
	if (cub3d->sprite.drawstart_x < 0)
		cub3d->sprite.drawstart_x = 0;
	cub3d->sprite.drawend_x =
		cub3d->sprite.sprite_w / 2 + cub3d->sprite.sprite_screen_x;
	if (cub3d->sprite.drawend_x >= cub3d->map.w)
		cub3d->sprite.drawend_x = cub3d->map.w - 1;
	cub3d->sprite.stripe = cub3d->sprite.drawstart_x;
	ft_ray_sprite_3(cub3d);
}

void	ft_ray_sprite_3(t_cub3d *cub3d)
{
	int y;

	y = 0;
	while (cub3d->sprite.stripe < cub3d->sprite.drawend_x)
	{
		cub3d->sprite.tex_x = (int)(256 *
			(cub3d->sprite.stripe - (-cub3d->sprite.sprite_w / 2 +
				cub3d->sprite.sprite_screen_x)) * cub3d->sprite.tex_w
				/ cub3d->sprite.sprite_w) / 256;
		if (cub3d->sprite.transform_y > 0 && cub3d->sprite.stripe > 0
			&& cub3d->sprite.stripe < cub3d->map.w && cub3d->sprite.transform_y
				< cub3d->sprite.z_buffer[cub3d->sprite.stripe])
		{
			y = cub3d->sprite.drawstart_y;
			ft_ray_sprite_4(cub3d, y);
		}
		cub3d->sprite.stripe++;
	}
}

void	ft_ray_sprite_4(t_cub3d *cub3d, int y)
{
	int k;

	k = 0;
	while (++y < (cub3d->sprite.drawend_y))
	{
		k = (y) * 256 - cub3d->map.h * 128 + cub3d->sprite.sprite_h * 128;
		cub3d->sprite.tex_y = ((k * cub3d->sprite.tex_h)
			/ cub3d->sprite.sprite_h) / 256;
		cub3d->data.color = cub3d->sprite.buffer[cub3d->sprite.tex_h
			* cub3d->sprite.tex_y + cub3d->sprite.tex_x];
		if (cub3d->data.color != 0)
			my_mlx_pixel_put(cub3d, cub3d->sprite.stripe, y, cub3d->data.color);
	}
}
