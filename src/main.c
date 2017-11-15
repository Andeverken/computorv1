#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

float		ft_atof(const char *str)
{
	float result;
	int i;

	result = 0;
	i = 1;
	while (*str == '\n' || *str == ' ' || *str == '\t' || *str == '\r' ||
			*str == '\v' || *str == '\f')
		str++;
	if (*str != '-' && *str != '+' && (*str < '0' || *str > '9'))
		return (0);
	if (*str == '-')
	{
		str++;
		if (*str == ' ')
			str++;
		while (*str >= '0' && *str <= '9' && *str)
			result = result * 10 + *str++ - 48;
		if (*str == '.')
		{
			if (*str == '.')
				str++;
			while (*str >= '0' && *str <= '9' && *str)
				result = result + (float)(*str++ - 48) / ft_power(10, i++);
		}
		result = -result;
	}
	else
	{
		if (*str == '+')
			str ++;
		if (*str == ' ')
			str++;
		while (*str >= '0' && *str <= '9' && *str)
			result = result * 10 + *str++ - 48;
		if (*str == '.')
		{
			if (*str == '.')
				str++;
			while (*str >= '0' && *str <= '9' && *str)
				result = result + (float)(*str++ - 48) / ft_power(10, i++);
		}
	}
	return (result);
}

double	sqrt(double a)
{
	double x = 1;
	int count = 0;

	while (count < 10)
	{
		x = (x + (a / x)) / 2;
		count++;
	}
	return (x);
}

int		count_first_part(char *str)
{
	int x;
	int count;

	x = 1;
	count = 1;
	while(str[x] != '=')
	{
		if (str[x] == '+' || str[x] == '-')
			count++;
		x++;
	}
	return (count);
}

int count_second_part(char *str)
{
	int x;
	int count;

	x = 0;
	count = 1;
	while(str[x] != '=')
		x++;
	x += 3;
	while(str[x])
	{
		if (str[x] == '+' || str[x] == '-')
			count++;
		x++;
	}
	return (count);
}

void		parseur(float **result, char *str)
{
	int part;
	int i;
	int power;

	part = 0;
	i = 0;
	power = 0;
	while (str[i])
	{
		result[part][power] = ft_atof(str + i);
		i++;
		power++;
		while (str[i] != '=' && str[i] != '+' && str[i] != '-' && str[i])
			i++;
		if (str[i] == '=')
		{
			i += 2;
			part = 1;
			power = 0;
		}
	}
}

void	reduction(float **result, int x, int y)
{
	int i;

	i = 0;
	while (i < x && i < y)
	{
		result[0][i] -= result[1][i];
		i++;
	}
	i = 0;
	printf("forme reduite : ");
	while (i < x)
	{
		if (result[0][i])
		{
			if (result[0][i] < 0)
			{
				printf("- ");
				printf("%f * X^%d ", -result[0][i], i);
			}
			else
			{
				if (i)
					printf("+");
				printf("%f * X^%d ", result[0][i], i);
			}
		}
		i++;
	}
	printf("= 0\n");
}

float	delta(int a, int b, int c)
{
	float delta;

	delta = b * b - (4 * a * c);
	return (delta);
}

void	resolve(float *result, float delta, int x)
{
	float z;
	float a;
	float complexe;

	z = 0;
	if (delta > 0)
	{
		z = (-result[1] - sqrt(delta)) / 2 * result[2];
		printf("%f\n", z);
		z = (-result[1] + sqrt(delta)) / 2 * result[2];
		printf("%f\n", z);
	}
	else if (delta == 0)
	{
		z = -result[1] / 2 * result[2];
		printf("%f\n", z);
	}
	else
	{
		a = result[2] * 2;
		complexe = sqrt(-delta) / a;
		printf("%f", -result[1] / a);
		if (complexe == 1)
			printf(" - i\n");
		else
			printf(" - %fi\n", complexe);
		printf("%f", -result[1] / a);
		if (complexe == 1)
			printf(" + i\n");
		else
			printf(" + %fi\n", complexe);
	}
	x = 0;
}

int		main(int argc, char **argv)
{
	int x;
	int y;
	float **result;

	if (argc != 2)
		return (0);
	printf("%f\n", sqrt(3));
	result = (float **)malloc(2 * sizeof(float *));
	x = count_first_part(argv[1]);
	y = count_second_part(argv[1]);
	printf("x = %d, y = %d\n", x, y);
	if (x > y)
		y = x;
	if (y > x)
		x = y;
	result[0] = (float *)malloc(x * sizeof(float));
	result[1] = (float *)malloc(y * sizeof(float));
	parseur(result, argv[1]);
	printf("%f,        %f\n", result[0][0], result[1][0]);
	reduction(result, x, y);
	resolve(result[0], delta(result[0][2], result[0][1], result[0][0]), x);
	return (0);
}
