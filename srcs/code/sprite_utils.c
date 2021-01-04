/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:16:34 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:22:52 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void	ft_sort_sprites(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	k;
	int	tmp;

	i = 0;
	while (++i < cub3d->sprite.num)
	{
		cub3d->sprite.distance = sqrt((pow(cub3d->xysp[i].x -
		cub3d->player.posx, 2.0)) + pow(cub3d->xysp[i].y
			- cub3d->player.posy, 2.0));
		cub3d->xysp[i].rel = cub3d->sprite.distance;
	}
	j = 0;
	while (++j < cub3d->sprite.num - 1 && (k = j + 1))
		while (++k < cub3d->sprite.num)
			if (cub3d->xysp[cub3d->sprite.order[j]].rel
				< cub3d->xysp[cub3d->sprite.order[k]].rel)
			{
				tmp = cub3d->sprite.order[j];
				cub3d->sprite.order[j] = cub3d->sprite.order[k];
				cub3d->sprite.order[k] = tmp;
			}
}

void	ft_res_sprites(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (!(cub3d->xysp = (t_xysp *)malloc(sizeof(t_xysp) * cub3d->sprite.num)))
		error_cub3d("\t------> \x1b[36mNo memory");
	if (!(cub3d->sprite.z_buffer = (double *)malloc(sizeof(double)
		* (cub3d->map.w + 1))))
		error_cub3d("\t------> \x1b[36mNo memory");
	if (!(cub3d->sprite.order = (int *)malloc(sizeof(int)
		* cub3d->sprite.num + 1)))
		error_cub3d("\t------> \x1b[36mNo memory");
}
