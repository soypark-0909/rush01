#include<stdio.h>
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
	end = start + 4;
	count = 0;
	max = input[start];
	flag = 0;
	while (start < end)
	{
		if	(input[index] == 0)
			break ;
		if (input[index] == 4)
		{
			count++;
			flag = 1;
			break ;
		}
		if (input[index] > max)
		{
			max = input[index];
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

int		check_row_right_height(int index, int *input, int look)
{

}

int		check_col_up_height(int index, int *input, int look)
{

}

int		check_col_down_height(int index, int *input, int look)
{

}

int		check_all(int index, int *input, t_look *cons)
{

}

void	write_table(int n, int *input)
{
	int		index;
	char	temp;
	//n by n 일때 출력을 인트형이 몇자리가 되느냐에 따라서 변경해야 함
	index = 0;
	while (index < n * n)
	{
		temp = input[index] + '0';
		write(1, input[index] + '0', 1);
		if(index % n == n - 1)
		{
			write(1, "\n", 1);
			continue ;
		}
		write(1, " ", 1);
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
		if(check_all(index, input, cons))
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

	table = malloc(sizeof(int) * (n));
	while (n > 0)
	{
		table[--n] = 0;
	}

	return (table);
}

t_look	*make_cons(int *constrain, int n)
{
	t_look		*result;
	t_look		temp;
	int			index;

	result = malloc(sizeof(t_look) * 4 * n);
	while (index < 2)
	{
		index++;
	}
}

int 	main(int argc, char *argv[])
{
	int		*input;
	t_look	*cons;
	int 	n;

	cons = make_cons(input, n);
	input = init_table(n);
	find_right_height(n, 0, input, cons);
	return (0);
}