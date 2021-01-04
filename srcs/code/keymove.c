/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 20:37:06 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:30 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void	ft_move_up_dowm(t_cub3d *cub3d)
{
	if (cub3d->keycode.w == 1)
	{
		if (cub3d->map.memoria[(int)(cub3d->player.posx + cub3d->player.dirx
		* cub3d->player.movespeed)][((int)cub3d->player.posy)] == '0')
			cub3d->player.posx += cub3d->player.dirx * cub3d->player.movespeed;
		if (cub3d->map.memoria[(int)cub3d->player.posx][(int)(cub3d->player.posy
			+ cub3d->player.diry * cub3d->player.movespeed)] == '0')
			cub3d->player.posy += cub3d->player.diry * cub3d->player.movespeed;
	}
	if (cub3d->keycode.s == 1)
	{
		if (cub3d->map.memoria[(int)(cub3d->player.posx - cub3d->player.dirx
			* cub3d->player.movespeed)][(int)cub3d->player.posy] == '0')
			cub3d->player.posx -= cub3d->player.dirx * cub3d->player.movespeed;
		if (cub3d->map.memoria[(int)cub3d->player.posx][(int)(cub3d->player.posy
			- cub3d->player.diry * cub3d->player.movespeed)] == '0')
			cub3d->player.posy -= cub3d->player.diry * cub3d->player.movespeed;
	}
}

void	ft_move_righ_left(t_cub3d *cub3d)
{
	if (cub3d->keycode.d)
	{
		if (cub3d->map.memoria[(int)(cub3d->player.posx)][((int)(cub3d->
		player.posy - cub3d->player.dirx * cub3d->player.movespeed))] == '0')
			cub3d->player.posy -= cub3d->player.dirx * cub3d->player.movespeed;
		if (cub3d->map.memoria[(int)(cub3d->player.posx + cub3d->player.diry
			* cub3d->player.movespeed)][(int)(cub3d->player.posy)] == '0')
			cub3d->player.posx += cub3d->player.diry * cub3d->player.movespeed;
	}
	if (cub3d->keycode.a)
	{
		if (cub3d->map.memoria
			[(int)(cub3d->player.posx)][((int)(cub3d->player.posy
			+ cub3d->player.dirx * cub3d->player.movespeed))] == '0')
			cub3d->player.posy += cub3d->player.dirx * cub3d->player.movespeed;
		if (cub3d->map.memoria[(int)(cub3d->player.posx - cub3d->player.diry
			* cub3d->player.movespeed)][(int)(cub3d->player.posy)] == '0')
			cub3d->player.posx -= cub3d->player.diry * cub3d->player.movespeed;
	}
}

void	ft_rot_righ(t_cub3d *cub3d)
{
	if (cub3d->keycode.righ)
	{
		cub3d->player.olddirx = cub3d->player.dirx;
		cub3d->player.dirx =
			cub3d->player.dirx * cos(-cub3d->player.rotspeed) -
			cub3d->player.diry * sin(-cub3d->player.rotspeed);
		cub3d->player.diry =
			cub3d->player.olddirx * sin(-cub3d->player.rotspeed)
			+ cub3d->player.diry * cos(-cub3d->player.rotspeed);
		cub3d->player.oldplanex = cub3d->player.planex;
		cub3d->player.planex = cub3d->player.planex *
			cos(-cub3d->player.rotspeed) - cub3d->player.planey
			* sin(-cub3d->player.rotspeed);
		cub3d->player.planey =
			cub3d->player.oldplanex * sin(-cub3d->player.rotspeed)
			+ cub3d->player.planey * cos(-cub3d->player.rotspeed);
	}
}

void	ft_rot_left(t_cub3d *cub3d)
{
	if (cub3d->keycode.left)
	{
		cub3d->player.olddirx = cub3d->player.dirx;
		cub3d->player.dirx =
			cub3d->player.dirx * cos(cub3d->player.rotspeed)
			- cub3d->player.diry * sin(cub3d->player.rotspeed);
		cub3d->player.diry =
			cub3d->player.olddirx * sin(cub3d->player.rotspeed)
			+ cub3d->player.diry * cos(cub3d->player.rotspeed);
		cub3d->player.oldplanex = cub3d->player.planex;
		cub3d->player.planex =
			cub3d->player.planex * cos(cub3d->player.rotspeed)
			- cub3d->player.planey * sin(cub3d->player.rotspeed);
		cub3d->player.planey =
			cub3d->player.oldplanex * sin(cub3d->player.rotspeed)
			+ cub3d->player.planey * cos(cub3d->player.rotspeed);
	}
}

int		key_move(t_cub3d *cub3d)
{
	if (cub3d->keycode.esc == 1)
	{
		write(1, "\n\x1b[36m[you have pressed the esc key!]\n", 38);
		mlx_clear_window(cub3d->data.mlx, cub3d->data.win);
		mlx_destroy_window(cub3d->data.mlx, cub3d->data.win);
		exit(0);
	}
	ft_move_up_dowm(cub3d);
	ft_move_righ_left(cub3d);
	ft_rot_righ(cub3d);
	ft_rot_left(cub3d);
	return (0);
}
