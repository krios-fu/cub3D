/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:06:26 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:55 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

int		ft_check_resolucion(t_cub3d *cub3d, int x)
{
	while (ft_is_space(&cub3d->map.tmp1[x]))
		x++;
	if (cub3d->map.tmp1[x] == 'R' && cub3d->map.tmp1[x + 1] == ' ')
		x++;
	while (ft_is_space(&cub3d->map.tmp1[x]))
		x++;
	if (!ft_isdigit(cub3d->map.tmp1[x]))
		error_cub3d("\t------> \x1b[36mInvalid resolution");
	cub3d->map.w = ft_atoi(&cub3d->map.tmp1[x]);
	while (ft_isdigit(cub3d->map.tmp1[x]))
		x++;
	while (ft_is_space(&cub3d->map.tmp1[x]))
		x++;
	cub3d->map.h = ft_atoi(&cub3d->map.tmp1[x]);
	while (ft_isdigit(cub3d->map.tmp1[x]))
		x++;
	if (cub3d->map.w < 1 || cub3d->map.h < 1)
		error_cub3d("\t------> \x1b[36mInvalid resolution");
	cub3d->map.w = (cub3d->map.w > 2560) ? 2560 : cub3d->map.w;
	cub3d->map.h = (cub3d->map.h > 1440) ? 1440 : cub3d->map.h;
	while (ft_is_space(&cub3d->map.tmp1[x]))
		x++;
	if (cub3d->map.tmp1[x] != '\0')
		error_cub3d("\t------> \x1b[36mInvalid resolution");
	return (0);
}

int		ft_check_ruta_norte(t_cub3d *cub3d, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	if (cub3d->map.ruta_norte)
		error_cub3d("\t------> \x1b[36mNorth route duplicated!");
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "NO ", 3) == 0)
		x = x + 3;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	cub3d->map.ruta_norte = ft_strtrim(tmp, " ");
	free(tmp);
	return (0);
}

int		ft_check_ruta_sur(t_cub3d *cub3d, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	if (cub3d->map.ruta_sur)
		error_cub3d("\t------> \x1b[36mSouth route duplicated!");
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "SO ", 3) == 0)
		x = x + 3;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	cub3d->map.ruta_sur = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	return (0);
}

int		ft_check_ruta_este(t_cub3d *cub3d, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	if (cub3d->map.ruta_este)
		error_cub3d("\t------> \x1b[36mWest route duplicated!");
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "WE ", 3) == 0)
		x = x + 3;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	cub3d->map.ruta_este = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	return (0);
}

int		ft_check_ruta_oeste(t_cub3d *cub3d, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	if (cub3d->map.ruta_oeste)
		error_cub3d("\t------> \x1b[36mEast route duplicated!");
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "EA ", 3) == 0)
		x = x + 3;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	cub3d->map.ruta_oeste = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	return (0);
}
