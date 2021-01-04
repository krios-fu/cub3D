/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:11:26 by krios-fu          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:51 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

int			ft_check_ruta_sprite(t_cub3d *cub3d, char *line)
{
	int		x;
	int		i;
	char	*tmp;

	i = 0;
	x = 0;
	if (cub3d->map.ruta_sprite)
		error_cub3d("\t------> \x1b[36mSprite duplicated!");
	while (line[x] == ' ')
		x++;
	if (ft_strncmp((line + x), "S ", 2) == 0)
		x = x + 2;
	while (line[x] == ' ')
		x++;
	tmp = ft_strdup(line + x);
	cub3d->map.ruta_sprite = ft_strtrim(tmp, " ");
	free(tmp);
	tmp = NULL;
	return (0);
}

void		ft_check_color_f(t_cub3d *cub3d, char *line)
{
	int		x;
	int		c;
	char	*tmp;
	char	**color;

	(cub3d->map.color_f >= 0)
		? error_cub3d("\t------> \x1b[36mDuplicated F!") : 0;
	x = 1;
	tmp = ft_strdup(line);
	while (tmp[x] == ' ')
		x++;
	if (ft_strncmp((tmp + x), "F ", 2) == 0)
		x = x + 2;
	color = ft_split(&tmp[x], ',');
	c = ft_rgb(color[0], color[1], color[2]);
	while (tmp[++x] != '\0')
	{
		if (tmp[x] == ',' && tmp[x + 1] == ',')
			error_cub3d("\t------> \x1b[36mInvalid color format!");
		if (!ft_isdigit(tmp[x]) && (tmp[x] != ',' && tmp[x] != ' '))
			error_cub3d("\t------> \x1b[36mInvalid color format!");
	}
	ft_free_var(color, tmp);
	free(color);
	cub3d->map.color_f = c;
}

void		ft_check_color_c(t_cub3d *cub3d, char *line)
{
	int		x;
	int		c;
	char	*tmp;
	char	**color;

	(cub3d->map.color_c >= 0)
		? error_cub3d("\t------> \x1b[36mDuplicated C!") : 0;
	x = 1;
	tmp = ft_strdup(line);
	while (tmp[x] == ' ')
		x++;
	if (ft_strncmp((tmp + x), "C ", 2) == 0)
		x = x + 2;
	color = ft_split(&tmp[x], ',');
	c = ft_rgb(color[0], color[1], color[2]);
	while (tmp[++x] != '\0')
	{
		if ((tmp[x] == ',' && tmp[x + 1] == ','))
			error_cub3d("\t------> \x1b[36mInvalid color format!");
		if (!ft_isdigit(tmp[x]) && (tmp[x] != ',' && tmp[x] != ' '))
			error_cub3d("\t------> \x1b[36mInvalid color format!");
	}
	ft_free_var(color, tmp);
	free(color);
	cub3d->map.color_c = c;
}

int			ft_rgb(char *r, char *g, char *b)
{
	int rgb;
	int r1;
	int g1;
	int b1;

	if (!r || !g || !b)
		error_cub3d("\t------> \x1b[36mInvalid color format!");
	r1 = ft_atoi(r);
	g1 = ft_atoi(g);
	b1 = ft_atoi(b);
	if (r1 > 255 || g1 > 255 || b1 > 255)
		error_cub3d("\t------> \x1b[36mColor > 255");
	rgb = r1;
	rgb = (rgb << 8) + g1;
	rgb = (rgb << 8) + b1;
	return (rgb);
}

void		ft_free_var(char **color, char *tmp)
{
	int i;

	i = 0;
	while (color[i])
	{
		free(color[i]);
		i++;
	}
	free(tmp);
	tmp = NULL;
}
