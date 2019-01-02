/*HEADER*/

#include "libft.h"

int	ft_tablen(char **tab)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (tab[++i])
		count++;
	return (count);
}
