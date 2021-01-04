/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:16 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:22:38 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void	ft_get_tex_no_so(t_cub3d *cub3d)
{
	if (cub3d->player.side == 0 && cub3d->player.stepx == -1)
	{
		cub3d->player.textura = cub3d->textura_norte.tex_norte;
		cub3d->player.buffer =
			(unsigned int *)mlx_get_data_addr(cub3d->player.textura,
			&cub3d->textura_norte.bits_per_pixel,
			&cub3d->textura_norte.line_lenght,
			&cub3d->textura_norte.endian);
	}
	if (cub3d->player.side == 0 && cub3d->player.stepx == 1)
	{
		cub3d->player.textura = cub3d->textura_sur.tex_sur;
		cub3d->player.buffer =
			(unsigned int *)mlx_get_data_addr(cub3d->player.textura,
			&cub3d->textura_sur.bits_per_pixel,
			&cub3d->textura_sur.line_lenght,
			&cub3d->textura_sur.endian);
	}
	ft_get_tex_we_ea(cub3d);
	cub3d->sprite.buffer =
		(unsigned int *)mlx_get_data_addr(cub3d->sprite.tex_add,
		&cub3d->sprite.bits_per_pixel, &cub3d->sprite.line_lenght,
		&cub3d->sprite.endian);
}

void	ft_get_tex_we_ea(t_cub3d *cub3d)
{
	if (cub3d->player.side == 1 && cub3d->player.stepy == 1)
	{
		cub3d->player.textura = cub3d->textura_este.tex_este;
		cub3d->player.buffer =
		(unsigned int *)mlx_get_data_addr(cub3d->player.textura,
		&cub3d->textura_este.bits_per_pixel,
		&cub3d->textura_este.line_lenght, &cub3d->textura_este.endian);
	}
	if (cub3d->player.side == 1 && cub3d->player.stepy == -1)
	{
		cub3d->player.textura = cub3d->textura_oeste.tex_oeste;
		cub3d->player.buffer =
		(unsigned int *)mlx_get_data_addr(cub3d->player.textura,
		&cub3d->textura_oeste.bits_per_pixel,
		&cub3d->textura_oeste.line_lenght,
		&cub3d->textura_oeste.endian);
	}
}

int		ft_check_lines(t_cub3d *cub3d, char *line)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (line[i] == ' ' || line[i] == '\n')
		i++;
	if (line[i] == 'R')
	{
		cub3d->map.tmp1 = line;
		x++;
		ft_check_resolucion(cub3d, x);
	}
	else
		ft_check_lines2(cub3d, line, i);
	return (0);
}

void	ft_check_lines2(t_cub3d *cub3d, char *line, int i)
{
	if (cub3d->map.xpvu > 1 && line[i] != ' ' && line[i] != '0'
		&& line[i] != '1' && line[i] != '2')
		error_cub3d("\t------> \x1b[36mInvalid map!");
	if (line[i] == 'N' && line[i + 1] == 'O')
		ft_check_ruta_norte(cub3d, line);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		ft_check_ruta_sur(cub3d, line);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		ft_check_ruta_este(cub3d, line);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		ft_check_ruta_oeste(cub3d, line);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		ft_check_ruta_sprite(cub3d, line);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		ft_check_color_f(cub3d, line);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ft_check_color_c(cub3d, line);
	else if (line[i] == ' ' || line[i] == '0'
		|| line[i] == '1' || line[i] == '2')
		ft_check_map(cub3d, line);
	else if (cub3d->map.xpvu > 1 && line[i] == 0)
		error_cub3d("\t------> \x1b[36mInvalid map!");
	if (cub3d->map.xpvu > 1 && line[i] != ' ' && line[i] != '0'
		&& line[i] != '1' && line[i] != '2')
		error_cub3d("\t------> \x1b[36mInvalid map!");
}

int		ft_is_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}
