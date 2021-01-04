/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parseo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:11:45 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:24 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void		ft_check_map(t_cub3d *cub3d, char *line)
{
	int		x;

	x = ft_strlen(line);
	cub3d->map.old = cub3d->map.old == 0 ? x : cub3d->map.old;
	if (cub3d->map.old < x)
		cub3d->map.old = x;
	cub3d->map.xpvu++;
}

void		ft_reservar_map(t_cub3d *cub3d)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(cub3d->map.memoria = malloc(sizeof(char*) * cub3d->map.xpvu)))
		error_cub3d("\t------> \x1b[36mNo memory");
	while (i < cub3d->map.xpvu)
	{
		j = 0;
		if (!(cub3d->map.memoria[i] = malloc(sizeof(char)
			* cub3d->map.old)))
			error_cub3d("\t------> \x1b[36mNo memory");
		while (j < cub3d->map.old)
		{
			cub3d->map.memoria[i][j] = '0';
			j++;
		}
		i++;
	}
}

void		ft_flood_fill(t_cub3d *cub3d, int x, int y)
{
	if (x < 0 || x >= cub3d->map.xpvu || y < 0 || y >= cub3d->map.old)
		error_cub3d("\t------> \x1b[36mOpen map!");
	if ((ft_strchr(" 0N2ESW", cub3d->map.memoria[x][y])))
	{
		if (cub3d->map.memoria[x][y] == '2')
		{
			--cub3d->sprite.tmp_num;
			cub3d->xysp[cub3d->sprite.tmp_num].x = x + 0.5;
			cub3d->xysp[cub3d->sprite.tmp_num].y = y + 0.5;
		}
		cub3d->map.memoria[x][y] = '*';
		ft_flood_fill(cub3d, x + 1, y);
		ft_flood_fill(cub3d, x, y + 1);
		ft_flood_fill(cub3d, x - 1, y);
		ft_flood_fill(cub3d, x, y - 1);
	}
}

char		**ft_cpy_memory(t_cub3d *cub3d, char **mem)
{
	char	**copy;
	int		i;

	if (!(copy = malloc(sizeof(char*) * cub3d->map.xpvu)))
		error_cub3d("\t\x1b[36m-------> No memory!");
	i = 0;
	while (i < cub3d->map.xpvu)
	{
		copy[i] = ft_strdup(mem[i]);
		i++;
	}
	return (copy);
}
