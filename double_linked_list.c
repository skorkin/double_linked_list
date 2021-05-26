#include <stdio.h>
#include <stdlib.h>

typedef struct	s_node
{
	void			*value;
	struct s_node	*prev;
	struct s_node	*next;
}				t_node;

typedef struct	s_d_list
{
	int			size;
	t_node		*head;
	t_node		*tail;
}				t_d_list;


t_d_list	*create_d_list() {
	t_d_list *tmp;

	tmp = (t_d_list*) malloc(sizeof(t_d_list));
	if (tmp == NULL)
		return (NULL);
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;

	return (tmp);
}

void	delete_d_list(t_d_list **list) {
	t_node *tmp;
	t_node *next;

	tmp = (*list)->head;
	next = NULL;
	while (tmp){
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}

void	push_front(t_d_list *list, void *data)
{
	t_node	*tmp;

	tmp = (t_node *)malloc(sizeof(t_node));
	if (tmp == NULL)
		return ;
	tmp->prev = NULL;
	tmp->next = list->head;
	tmp->value = data;
	if (list->head)
		list->head->prev = tmp;
	if (list->tail == NULL)
		list->tail = tmp;
	list->head = tmp;
	list->size++;
}

void	*pop_front(t_d_list *list)
{
	t_node	*prev;
	void	*tmp;

	if (list->head == NULL)
		return (NULL);
	prev = list->head;
	list->head = list->head->next;
	if (list->head)
		list->head->prev = NULL;
	if (prev == list->tail)
		list->tail = NULL;
	tmp = prev->value;
	free(prev);
	list->size--;
	return (tmp);
}


void	push_back(t_d_list *list, void *value)
{
	t_node	*tmp;
	tmp = (t_node *)malloc(sizeof(t_node));
	if (tmp == NULL) {
		exit(3);
	}
	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;
 
	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}
 
void	*pop_back(t_d_list *list) {
	t_node	*next;
	void	*tmp;

	if (list->tail == NULL)
		return (NULL);
	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
		list->tail->next = NULL;
	if (next == list->head)
		list->head = NULL;
	tmp = next->value;
	free(next);
	list->size--;
	return (tmp);
}


t_node	*get_n_el(t_d_list *list, size_t index) {
	t_node *tmp;
	size_t i;

	tmp = NULL;
	if (index < list->size/2) {
		i = 0;
		tmp = list->head;
		while (tmp && i < index) {
			tmp = tmp->next;
			i++;
		}
	} else {
		i = list->size - 1;
		tmp = list->tail;
		while (tmp && i > index) {
			tmp = tmp->prev;
			i--;
		}
	}
	return (tmp);
}

void insert(t_d_list *list, size_t index, void *value) {
	t_node *elm;
	t_node *ins;

	elm = NULL;
	ins = NULL;
	elm = get_n_el(list, index);
	if (elm == NULL)
		return ;
	ins = (t_node*) malloc(sizeof(t_node));
	ins->value = value;
	ins->prev = elm;
	ins->next = elm->next;
	if (elm->next)
		elm->next->prev = ins;
	elm->next = ins;
	if (!elm->prev)
		list->head = elm;
	if (!elm->next)
		list->tail = elm;
	list->size++;
}
 
void	*delete_n(t_d_list *list, size_t index) {
	t_node	*elm;
	void	*tmp;

	elm = NULL;
	tmp = NULL;
	elm = get_n_el(list, index);
	if (elm == NULL)
		return (NULL);
	if (elm->prev)
		elm->prev->next = elm->next;
	if (elm->next)
		elm->next->prev = elm->prev;
	tmp = elm->value;
	if (!elm->prev)
		list->head = elm->next;
	if (!elm->next)
		list->tail = elm->prev;
	free(elm);
	list->size--;
	return (tmp);
}

void print_d_list(t_d_list *list, void (*fun)(void*)) {
	t_node *tmp = list->head;
	while (tmp) {
		fun(tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

void print_int(void *value) {
	printf("%d ", *((int*) value));
}

t_d_list	*from_arr(void *arr, size_t n, size_t size) {
	t_d_list *tmp;
	size_t		i;

	i = 0;
	tmp = NULL;
	if (arr == NULL)
		return (NULL);
	tmp = create_d_list();
	while (i < n) {
		push_back(tmp, ((char*)arr + i*size));
		i++;
	}
	return (tmp);
}

int main()
{
	t_d_list *list;

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;
	int e = 50;
	int f = 60;
	int g = 70;
	int h = 80;
	list = create_d_list();
	push_front(list, &a);
	push_front(list, &b);
	push_front(list, &c);
	push_front(list, &d);
	push_front(list, &e);
	print_d_list(list, print_int);
}