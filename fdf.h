/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/10 17:21:22 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/11 17:45:11 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include "get_next_line.h"

typedef struct	s_window
{
    void		*mlx;
    void		*win;
	int			width;
	int			height;
}				s_window;

typedef struct	s_dot
{
	float		x;
	float		y;
}				s_dot;

typedef struct	s_par
{
	s_dot		d1;
	s_dot		d2;
	s_dot		d3;
	s_dot		d4;
}				s_par;

typedef struct	s_vector
{
	float	x;
	float	y;
}				s_vector;

typedef struct	s_inputs
{
	int		fd;
	char	*line;
	char	**tabstr;
	int		lenx;
	int		leny;
	int		*tmp;
	int		**tab;
}				s_inputs;

typedef struct		s_map
{
	s_dot		origin;
	s_dot		centre;
	s_vector	i;
	s_vector	j;
	s_vector	k;
	s_dot		***tabdot;
	float		zoom;
}			s_map;

void			ft_put_line(s_window *window, s_dot *d1, s_dot *d2, int color);
void			ft_put_par(s_window *win, s_par par, int color);
int				set_dots(s_window *win, s_inputs *inputs, s_map *map);
void			print_dots(s_window *win, s_inputs *inputs, s_map *map);
s_par			set_par(s_dot *d1, s_dot *d2, s_dot *d3, s_dot *d4);
#endif
