/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 16:03:40 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:35 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

int	ft_keypress(int key, t_cub3d *cub3d)
{
	if (key == KEY_UP && (cub3d->keycode.w == 0))
		cub3d->keycode.w = 1;
	if (key == KEY_DOWN && (cub3d->keycode.s == 0))
		cub3d->keycode.s = 1;
	if (key == KEY_RIGHT && (cub3d->keycode.d == 0))
		cub3d->keycode.d = 1;
	if (key == KEY_LEFT && (cub3d->keycode.a == 0))
		cub3d->keycode.a = 1;
	if (key == KEY_RIGHT_VISION && (cub3d->keycode.righ == 0))
		cub3d->keycode.righ = 1;
	if (key == KEY_LEFT_VISION && (cub3d->keycode.left == 0))
		cub3d->keycode.left = 1;
	if (key == ESC && (cub3d->keycode.esc == 0))
		cub3d->keycode.esc = 1;
	return (0);
}

int	ft_keyrelease(int key, t_cub3d *cub3d)
{
	if (key == KEY_UP && (cub3d->keycode.w == 1))
		cub3d->keycode.w = 0;
	if (key == KEY_DOWN && (cub3d->keycode.s == 1))
		cub3d->keycode.s = 0;
	if (key == KEY_RIGHT && (cub3d->keycode.d == 1))
		cub3d->keycode.d = 0;
	if (key == KEY_LEFT && (cub3d->keycode.a == 1))
		cub3d->keycode.a = 0;
	if (key == KEY_RIGHT_VISION && (cub3d->keycode.righ == 1))
		cub3d->keycode.righ = 0;
	if (key == KEY_LEFT_VISION && (cub3d->keycode.left == 1))
		cub3d->keycode.left = 0;
	return (0);
}
