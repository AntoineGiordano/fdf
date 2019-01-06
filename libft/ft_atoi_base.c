/*HEADER*/

#include "libft.h"

static int	is_base(char c, int base)
{
	char	*carac_base;
	int	i;

	carac_base = "0123456789ABCDEFGHIJKLMNOPQURSTUVWXYZ";
	i = -1;
	while (++i < base)
		if (c == carac_base[i] || c == ft_tolower(carac_base[i]))
			return (i);
	return (-1);
}

int		ft_atoi_base(const char *str, int base)
{
	long	nbr;
	int	sign;
	int	i;

	nbr = 0;
	sign = 1;
	i = -1;
	while ((str[++i] >= 9 && str[i] <= 13) || str[i] == ' ');
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (is_base(str[i], base) != -1)
		nbr = nbr * base + is_base(str[i++], base);
	return ((int)(nbr * sign));
}
