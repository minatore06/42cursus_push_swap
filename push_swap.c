/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:32:59 by scaiazzo          #+#    #+#             */
/*   Updated: 2023/01/09 14:33:02 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
//22 24 12 7 14 16 3 15 17 19 9 18 25 6 10 8 23 11 20 5 21 1 4 13 2 
void	print_stack(t_stack *s)
{
	while (s)
	{
		////ft_printf("A: %d | ", s->x);
		s = s->next;
	}
	////ft_printf("\n");
}

t_stack *manage_input(char **argv)
{
	t_stack	*input;
	int	n;
	int	i;
	int	j;

	input = 0;
	i = 1;
	while (argv[i])
	{
		j= 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != '-')
				break ;
			j++;
		}
		if (j != ft_strlen(argv[i]))
			return (input);
		n = ft_atoi(argv[i]);
		ft_lstadd_back(&input, ft_lstnew(n));
		i++;
	}
	return (input);
}

void	move_to_b(t_stack **A, t_stack **B, t_stack *el)
{
	put_first(A, el);
	pb(A, B);
}

void	swap2el(t_stack **A, t_stack **B, t_stack *el1, t_stack *el2)
{
	t_stack	*go_first;

	if (get_next(*A, el1) == el2)
	{
		put_first(A, el1);
		sa(A, 1);
		return;
	}
	go_first = get_next(*A, el1);
	move_to_b(A, B, el1);
	move_to_b(A, B, el2);
	//print_stack(*A);
	sb(B, 1);
	pa(A, B);
	put_first(A, go_first);
	pa(A, B);
	//print_stack(A.head);
}

void	swap_pivot(t_stack **A, t_stack **B, t_stack *last, t_stack *el2)
{
	t_stack	*go_first;

	go_first = get_next(*A, last);
	if (go_first == el2)
		go_first = get_next(*A, el2);
	if (!go_first)
	{
		//ft_printf("sos\n");
		go_first = *A;
	}
	move_to_b(A, B, el2);
	//print_stack(*A);
	sb(B, 1);
	pa(A, B);
	put_first(A, go_first);
	pa(A, B);
	//print_stack(A.head);
}

t_stack	*get_first_bigger(t_stack *lst, t_stack *start, int pivot)
{
	int		size;

	size = ft_lstsize(lst);
	while (size--)
	{
		////ft_printf("%d\n", lst->x);
		if (start->x > pivot && !start->right)
			return (start);
		start = get_next(lst, start);
	}
	return (0);
}

t_stack	*get_last_smaller(t_stack *lst, t_stack *start, int pivot)
{
	t_stack	*small;
	int		size;
	int		i;

	size = ft_lstsize(lst) - 1;
	while (size >= 0)
	{
		small = start;
		i = 0;
		while (size - i++)
			small = get_next(lst, small);
		size--;
		if (small->x < pivot && !small->right)
			return (small);
	}
	return (0);
}

t_stack	*get_smaller(t_stack *A)
{
	t_stack	*min;

	min = A;
	while (A)
	{
		if (A->x < min->x)
			min = A;
		A = A->next;
	}
	return (min);
}

int	left_is_right(t_stack *lst, t_stack *start, t_stack *big, t_stack *small)
{
	//ft_printf("small: %d, big: %d\n", small->x, big->x);
	if (small == start)
		return (1);
	while (small != start)
	{
		if (small == big)
			return (1);
		small = get_next(lst, small);
	}
	return (0);
}

int	is_order(t_stack *lst, t_stack *start, t_stack *end)
{
	int	old;

	old = start->x;
	start = get_next(lst, start);
	while (start != end)
	{
		//ft_printf("hello\n");
		if (old > start->x)
			return (0);
		old = start->x;
		start = get_next(lst, start);
	}
	return (1);
}

void	sort(t_ez_stack *A, t_stack **B, t_stack *first, t_stack *last)
{
	t_stack *pivot;
	t_stack	*big_left;
	t_stack	*small_right;
//IF PIVOT SWAPS WITH FIRST OR LAST (risolto forse)
//IF PIVOT IS FIRST OR LAST (risolto forse)
	if (first)
		//ft_printf("first %d\n", first->x);
	if (last)
		//ft_printf("last %d\n", bfrthis(A->head, last)->x);
	if (get_next(A->head, first) == last)
		return ;
	if (is_order(A->head, first, last))
		return ;
	//ft_printf("bfr last %p\n", last);
	pivot = get_pivot(A->head, first, bfrthis(A->head, last));
	//ft_printf("size: %d, pivot %d\n",ft_lstsize(A->head), pivot->x);
	if (pivot == first)
		first = get_next(A->head, pivot);
	if (pivot == last)
		last = bfrthis(A->head, pivot);
	move_to_b(&A->head, B, pivot);
	while (1)
	{
		big_left = get_first_bigger(A->head, A->start, pivot->x);
		small_right = get_last_smaller(A->head, A->start, pivot->x);
		if (left_is_right(A->head, A->start, big_left, small_right))
			break;
		else
			swap2el(&A->head, B, big_left, small_right);
		if (big_left == first)
			first = small_right;
	}
	if (big_left == first)
		first = get_next(A->head, pivot);
	//ft_printf("MEGA\n");
	swap_pivot(&A->head, B, bfrthis(A->head, last), big_left);
	pivot->right = 1;
	if (get_distance(A->head, first, pivot) == 2)
	{
		//ft_printf("21\n");
		small_right = bfrthis(A->head, pivot);
		if (bfrthis(A->head, small_right)->x > small_right->x)
			swap2el(&A->head, B, bfrthis(A->head, small_right), small_right);
		else
		{
			small_right->right = 1;
			bfrthis(A->head, small_right)->right = 1;
		}
	}
	else if (get_distance(A->head, first, pivot) == 1){
		//ft_printf("?\n");
		bfrthis(A->head, pivot)->right = 1;}
	else{
		//ft_printf("REDO1 %d\n", pivot->x);
		sort(A, B, first, pivot);}
	if (get_distance(A->head, pivot, bfrthis(A->head, last)) == 2)
	{
		//ft_printf("22\n");
		pivot = get_next(A->head, pivot);
		if (pivot->x > get_next(A->head, pivot)->x)
			swap2el(&A->head, B, pivot, get_next(A->head, pivot));
		else
		{
			pivot->right = 1;
			get_next(A->head, pivot)->right = 1;
		}
	}
	else if (get_distance(A->head, pivot, bfrthis(A->head, last)) == 1)
	{
		//ft_printf("???\n");
		get_next(A->head, pivot)->right = 1;
	}
	else
	{
		//ft_printf("REDO2 %d\n", pivot->x);
		sort(A, B, get_next(A->head, pivot), last);
	}
}

int	main(int argc, char *argv[])
{
	t_ez_stack A;
	t_stack *B;

	if (argc < 2)
		return (0);
	A.head = manage_input(argv);
	A.start = get_smaller(A.head);
	put_first(&A.head, A.start);
	B = 0;	
/* 	if (is_order(A))
		return ; */
	sort(&A, &B, A.start, A.start);
	//print_stack(A.head);
	put_first(&A.head, A.start);
	return (0);
}
