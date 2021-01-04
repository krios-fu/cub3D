/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parseo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 10:13:12 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:19 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void		ft_check_memoria(t_cub3d *cub3d)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while ((++i) < cub3d->map.xpvu)
	{
		j = 0;
		while ((++j) < cub3d->map.old)
		{
			c = cub3d->map.memoria[i][j];
			if (!(ft_strchr(" 012NESW", c)))
				error_cub3d("\t------> \x1b[36mInvalid character!");
			if (c == '2')
				cub3d->sprite.num++;
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				ft_player_pos(cub3d, c, j, i);
			if ((ft_strchr(" NESW", c)))
				cub3d->map.memoria[i][j] = '0';
		}
	}
	if (cub3d->player.nswe == '\0')
		error_cub3d("\t------> \x1b[36mNo player!\n");
	ft_map(cub3d);
}

void		ft_player_pos(t_cub3d *cub3d, char c, int j, int i)
{
	if (cub3d->player.nswe == '\0')
	{
		cub3d->player.nswe = c;
		cub3d->player.posy = j + 0.5;
		cub3d->player.posx = i + 0.5;
	}
	else
		error_cub3d("\t------> \x1b[36mMultiplayer!\n");
}

void		ft_map(t_cub3d *cub3d)
{
	char	**copy_mem;

	cub3d->sprite.tmp_num = cub3d->sprite.num;
	if (cub3d->player.posx == -1 && cub3d->player.posy == -1)
		error_cub3d("\t------> \x1b[36mNo player!");
	copy_mem = ft_cpy_memory(cub3d, cub3d->map.memoria);
	ft_res_sprites(cub3d);
	ft_flood_fill(cub3d, (int)cub3d->player.posx, (int)cub3d->player.posy);
	ft_free_matriz(cub3d, cub3d->map.memoria);
	cub3d->map.memoria = ft_cpy_memory(cub3d, copy_mem);
	ft_free_matriz(cub3d, copy_mem);
	ft_no_so(cub3d);
}

void		ft_fill_map(t_cub3d *cub3d, char **argv)
{
	char	*line;
	int		fd;
	int		j;
	int		w;

	fd = open(argv[1], O_RDONLY);
	w = 0;
	while (get_next_line(fd, &line) > 0 && (j = -1))
	{
		while (line[j++] == ' ')
			line[j] = '0';
		if (line[j] == '0' || line[j] == '1' || line[j] == '2')
			ft_strlcpy(cub3d->map.memoria[w++], line, ft_strlen(line) + 1);
		free(line);
		line = NULL;
	}
	j = 0;
	while (line[++j] == ' ')
		line[j] = '0';
	if (line[j] != '\0')
		ft_strlcpy(cub3d->map.memoria[w++], line, ft_strlen(line) + 1);
	free(line);
	close(fd);
	ft_check_memoria(cub3d);
}

void		ft_free_matriz(t_cub3d *cub3d, char **matriz)
{
	int i;

	i = 0;
	while (i < cub3d->map.xpvu)
	{
		free(matriz[i]);
		i++;
	}
	free(matriz);
}
