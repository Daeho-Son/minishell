#include "../includes/list_node.h"

void	print_list(t_list *list)
{
	printf("### print_list\n");
	t_node	*node;

	if (!list)
	{
		printf("NULL list\n");
		return ;
	}
	while (list)
	{
		printf("- l_type: %d\n", list->l_type);
		node = list->start_node;
		while (node)
		{
			printf("-- n_type: %d\n", node->n_type);
			printf("-- data: %s\n", node->data);
			node = node->next;
		}
		printf("\n");
		list = list->next;
	}
}

void	print_node(t_node *node)
{
	printf("### print_node\n");
	if (!node)
	{
		printf("NULL node\n");
		return ;
	}
	while (node)
	{
		printf("- n_type: %d\n", node->n_type);
		printf("- data: %s\n", node->data);
		node = node->next;
	}
	printf("\n");
}