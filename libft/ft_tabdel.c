/*HEADER*/

#include "libft.h"

void	ft_tabdel(char ***tab)
{
	int	i;

	i = -1;
	while ((*tab)[++i])
		ft_strdel(*tab + i);
	free(*tab);
	*tab = NULL;
}
