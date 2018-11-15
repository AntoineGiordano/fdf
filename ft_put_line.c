/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_set_line.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/12 14:59:37 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/12 14:59:38 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "fdf.h"

float	ft_abs(float x)
{
	if (x >= 0)
		return (x);
	else
		return (-x);
}

void	ft_put_line(s_window window, s_dot *d1, s_dot *d2, int color)
{
	float		dx;
	float		dy;
	int			nbpixels;
	int			i;

	printf("x1 = %f\ny1 = %f\n", d1->x, d1->y);
	printf("x2 = %f\ny2 = %f\n\n\n\n\n", d2->x, d2->y);
	dx = d2->x - d1->x;
	dy = d2->y - d1->y;
	if (ft_abs(dx) > ft_abs(dy))
	{
		nbpixels = dx;
		dy /= ft_abs(dx);
		dx /= ft_abs(dx);
	}
	else
	{
		nbpixels = dy;
		dx /= ft_abs(dy);
		dy /= ft_abs(dy);
	}
	i = -1;
	while (i++ < nbpixels)
		mlx_pixel_put(window.mlx, window.win,
		d1->x + dx * i, d1->y + dy * i, color);
}
