/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 23:11:19 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:15 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void	ft_draw_ray(t_cub3d *cub3d, int x)
{
	int y;

	y = 0;
	while (y < cub3d->player.drawstart)
	{
		my_mlx_pixel_put(cub3d, x, y, cub3d->map.color_c);
		y++;
	}
	y = cub3d->player.drawstart;
	ft_get_tex_no_so(cub3d);
	while (y++ < cub3d->player.drawend)
	{
		cub3d->player.texy = (int)cub3d->player.texpos;
		cub3d->player.texpos += cub3d->player.step;
		cub3d->data.color = cub3d->player.buffer[cub3d->player.tex_w
			* cub3d->player.texy + cub3d->player.texx];
		my_mlx_pixel_put(cub3d, x, y, cub3d->data.color);
	}
	y--;
	while (y++ < cub3d->map.h)
		my_mlx_pixel_put(cub3d, x, y, cub3d->map.color_f);
	cub3d->sprite.z_buffer[x] = cub3d->player.perpwalldist;
}
