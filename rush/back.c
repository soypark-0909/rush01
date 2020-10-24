#include<stdlib.h>
#include<unistd.h>

typedef struct  s_look
{
	int 	left;
	int		right;
}	t_look;;

int 	check_row_number(int n,int index, int *input)
{
	int		start;

	start = (index / n) * n;
	while (start < n)
	{
		if (input[index] == input[start])
			return (0);
		start++;
	}
	return (1);
}

int		check_col_number(int n, int index, int *input)
{
	int		start;
	int		seat;

	start = index % n;
	seat = 0;
	while (seat < n)
	{
		if (input[seat * n + start] == input[index])
			return (0);
		seat++;
	}
	return (1);
}

int		check_row_left_height(int n, int index, int *input, int look)
{
	int		start;
	int		end;
	int		count;
	int		max;
	int 	flag;

	start = (index / n) * n;
	end = start + n;
	count = 1;
	max = input[start];
	flag = 0;
	while (start < end)
	{
		if	(input[start] == 0)
			break ;
		if (input[start] == n)
		{
			count++;
			flag = 1;
			break ;
		}
		if (input[start] > max)
		{
			max = input[start];
			count++;
		}
		start++;
	}
	if (flag && count == look)
		return (1);
	else if(!flag && count < look)
		return (1);
	else
		return (0);
}

int		check_row_right_height(int n, int index, int *input, int look)
{

}

int		check_col_up_height(int n, int index, int *input, int look)
{

}

int		check_col_down_height(int n, int index, int *input, int look)
{
	int		start;
	int		end;
	int		count;
	int		max;
	int		flag;

	start = (index % n) + (n) * (n - 1);
	end = (index % n);
	count = 1;
	while (start <= end)
	{
		if	(input[start] == 0)
			break ;
		if (input[start] == n)
		{
			count++;
			flag = 1;
			break ;
		}
		if (input[start] > max)
		{
			max = input[start];
			count++;
		}
		start -= n;
	}
	if (flag && count == look)
		return (1);
	else if(!flag && count < look)
		return (1);
	else
		return (0);
}

int		check_all(int n, int index, int *input, t_look *cons)
{
	if (!check_col_number(n, index, input))
		return (0);
	else if (!check_row_number(n, index, input))
		return (0);
	else if (!check_row_right_height(n, index, input, cons[index / n + 1].left))
		return (0);
	else if (!check_row_left_height(n, index, input, cons[index / n + 1].left))
		return (0);
	else if (!check_col_up_height(n, index, input, cons[index % n].left ))
		return (0);
	else if (!check_col_down_height(n, index, input, cons[index % n].right))
		return (0);
	else
		return (1);
}

void	write_table(int n, int *input)
{
	int		index;

	index = 0;
	while (index < n * n)
	{
		write_nbr(input[index]);
		if(index % n == n - 1)
		{
			write(1, "\n", 1);
			continue ;
		}
		write(1, " ", 1);
		index++;
	}
}

int 	find_right_height(int n, int index, int *input, t_look *cons)
{
	int		num;

	if(index = n * n)
	{
		write_table(n, input);
		return (1);
	}
	num = 1;
	while (num <= n)
	{
		input[index] = num;
		if(check_all(n, index, input, cons))
		{
			if(find_right_height(n, index + 1, input, cons))
			{
				return (1);
			}
		}
		num++;
	}
	return (0);
}

int		*init_table(int n)
{
	int 	*table;
	int		index;

	table = malloc(sizeof(int) * (n) * (n));
	index = (n) * (n);
	while (index > 0)
	{
		table[--index] = 0;
	}

	return (table);
}

int		ft_atoi(char *str)
{
	int		result;

	while (*str != '\0')
	{
		if (*str >= '0' && *str >= '9')
		{
			result = result * 10 + (*str - '0');
		}
		else
			return (-1);
	}
	return (result);
}

void	write_nbr(int nbr)
{
	if(nbr / 10 == 0)
	{
		write(1, "0123456789"[nbr % 10], 1);
		return ;
	}
	write_nbr(nbr / 10);
}

int		preprocess(int argc, char *argv[], int *input, int n)
{
	int		index;
	int		temp;
	
	if (argc != 4 * (n) + 1)
		return (0);
	index = 0;
	while (index < argc - 1)
	{
		temp  = ft_atoi(argv[index + 1]);
		if (temp > n || temp < 0)
			return (0);
		input[index] = ft_atoi(argv[index + 1]);
		index++;
	}
	return (1);
}

t_look	*make_cons(int *constrain, int n)
{
	t_look		*result;
	t_look		temp;
	int			index;
	int			r_index;

	result = malloc(sizeof(t_look) * 4 * n);
	index = 0;
	r_index = 0;
	while (index < n)
	{
		temp.left = constrain[index];
		temp.right = constrain[index + n];
		result[r_index++] = temp;
		temp.left = constrain[index + 2 * n];
		temp.right = constrain[index + 3 * n];
		result[r_index++] = temp;
		index++;
	}
	return (result);
}

int 	main(int argc, char *argv[])
{
	int		*input;
	int		*table;
	t_look	*cons;
	int 	n;

	n = 4;
	input = malloc(sizeof(int) * n * 4);
	if(!preprocess(argc, argv, input, n))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	cons = make_cons(input, n);
	table = init_table(n);
	if(find_right_height(n, 0, table, cons))
		return (0);
	else
		write(1, "Error\n", 6);
	return (0);
}