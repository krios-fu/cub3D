/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krios-fu <krios-fu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:26:28 by abello-r          #+#    #+#             */
/*   Updated: 2021/01/04 14:23:06 by krios-fu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3dlib.h"

void	ft_bit_rgb(unsigned char *s, int i)
{
	s[0] = (unsigned char)i;
	s[1] = (unsigned char)(i >> 8);
	s[2] = (unsigned char)(i >> 16);
	s[3] = (unsigned char)(i >> 24);
}

void	ft_bmp_cabezera(t_cub3d *cub3d, int fd, int ps)
{
	unsigned char	header[54];
	int				filesize;

	filesize = 54 + (cub3d->map.w * 3 * cub3d->map.h) +
		(ps * cub3d->map.w);
	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	ft_bit_rgb(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	ft_bit_rgb(header + 18, cub3d->map.w);
	ft_bit_rgb(header + 22, -cub3d->map.h);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
	write(fd, cub3d->data.addr, cub3d->map.w * cub3d->map.h * 4);
}

int		ft_screenshot(t_cub3d *cub3d)
{
	int				fd;
	int				padsize;

	padsize = (4 - (cub3d->map.w * 3) % 4) % 4;
	write(1, "\n\x1b[36m[Screenshot] \t Route: ./srcs/utils/cub3D.bmp\n", 51);
	if (!(fd = open("./srcs/cub3D.bmp", O_WRONLY | O_CREAT, S_IRWXU |
	O_TRUNC | O_APPEND)))
		error_cub3d("\t------> \x1b[36mScreenshot could not be created!");
	ft_bmp_cabezera(cub3d, fd, padsize);
	close(fd);
	exit(0);
	return (1);
}
