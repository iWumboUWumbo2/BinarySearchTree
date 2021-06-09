#include "tree.h"
#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/***** NODE *****/

tree_node_t* tree_node_init(int value) {
	tree_node_t* node = malloc(sizeof(tree_node_t));
	node->value = value;
	node->ltNode = node->rtNode = NULL;
	return node;
}

void tree_node_free(tree_node_t* node) {
	if (node != NULL) {
		tree_node_free(node->ltNode);
		tree_node_free(node->rtNode);
		free(node);
	}
}

void tree_node_insert(tree_node_t** root, tree_node_t* node, int* size) {
	if (*root == NULL) {
		node->number = *size;
		*root = node;
		(*size)++;
	}
	else {
		if ((*root)->value == node->value) {
			free(node);
			return;
		}
		
		if ((*root)->value > node->value)
			tree_node_insert(&((*root)->ltNode), node, size);
		else
			tree_node_insert(&((*root)->rtNode), node, size);
	}
}

void tree_node_print_generic(const tree_node_t* node) {
	if (node != NULL) {
		tree_node_print_generic(node->ltNode);
		printf("(%d: %d) ", node->number, node->value);
		tree_node_print_generic(node->rtNode);
	}
}

void tree_node_dfs_recur(const tree_node_t* node, int* visited) {
	visited[node->number] = 1;
	printf("(%d: %d) ", node->number, node->value);
	tree_node_t* adjNodes[2] = {node->ltNode, node->rtNode};
	for (int i = 0; i < 2; i++) {
		if (adjNodes[i] != NULL) {
			if (!visited[adjNodes[i]->number]) {
				tree_node_dfs_recur(adjNodes[i], visited);
			}
		}
	}
}

/***** TREE *****/

void tree_init(tree_t* tree) {
	tree->root = NULL;
	tree->size = 0;
}

void tree_add_recur(tree_t* tree, int value) {
	tree_node_t* node = tree_node_init(value);
	tree_node_insert(&tree->root, node, &tree->size);
}
		
void tree_add_iter(tree_t* tree, int value) {
	tree_node_t* node = tree_node_init(value);
	node->number = tree->size;
	
	if (tree->root == NULL) {
		tree->root = node;
		tree->size++;
		return;
	}
	
	tree_node_t* ptr = tree->root;
	tree_node_t* prevPtr = NULL;
	unsigned char isLeft = 0;
	while (ptr != NULL) {
		prevPtr = ptr;
		if (ptr->value == value) {
			free(node);
			return;
		}
		
		isLeft = ptr->value > value;
		ptr = isLeft ? ptr->ltNode : ptr->rtNode;
	}
	
	if (isLeft)
		prevPtr->ltNode = node;
	else 
		prevPtr->rtNode = node;
	
	tree->size++;
}

void tree_add_array(tree_t* tree, const int* arr, int size, const void (*tree_add) (tree_t*, int)) {
	for (int i = 0; i < size; i++) {
		tree_add(tree, arr[i]);
	}
}	

void tree_print_generic(const tree_t* tree) {
	tree_node_print_generic(tree->root);
}

void tree_bfs(const tree_t* tree) {
	deque_t deque;
	deque_init(&deque);
	int* visited = calloc(tree->size, sizeof(int));
	
	deque_enqueue(&deque, deque_node_init(tree->root));
	visited[tree->root->number] = 1;
	
	while(deque.size > 0) {
		tree_node_t* node = deque_dequeue(&deque)->value;
		printf("(%d: %d) ", node->number, node->value);
		
		tree_node_t* adjNodes[2] = {node->ltNode, node->rtNode};
		for (int i = 0; i < 2; i++) {
			if (adjNodes[i] != NULL) {
				if (!visited[adjNodes[i]->number]) {
					visited[adjNodes[i]->number] = 1;
					deque_enqueue(&deque, deque_node_init(adjNodes[i]));
				}
			}
		}
	}
	
	free(visited);
	deque_free(&deque);
}

void tree_dfs_recur(const tree_t* tree) {
	int* visited = calloc(tree->size, sizeof(int));
	tree_node_dfs_recur(tree->root, visited);
	free(visited);
}

void tree_dfs_iter(const tree_t* tree) {
	deque_t stack;
	deque_init(&stack);
	int* visited = calloc(tree->size, sizeof(int));
	
	deque_enqueue(&stack, deque_node_init(tree->root));
	
	while (stack.size > 0) {
		tree_node_t* node = deque_pop(&stack)->value;
		printf("(%d: %d) ", node->number, node->value);
		
		if (!visited[node->number]) {
			visited[node->number] = 1;
			tree_node_t* adjNodes[2] = {node->ltNode, node->rtNode};
			for (int i = 0; i < 2; i++) {
				if (adjNodes[i] != NULL) {
					deque_push(&stack, deque_node_init(adjNodes[i]));
				}
			}
		}
	}
	
	free(visited);
	deque_free(&stack);
}

void tree_free(tree_t* tree) {
	tree_node_free(tree->root);
}

void tree_print(const tree_t* tree, const char* printer, const void (*tree_printer) (const tree_t*)) {
	printf("%s\n", printer);
	printf("Root: %d\n", tree->root->value);
	printf("Tree: ");
	tree_printer(tree);
	printf("\nSize: %d", tree->size);
}

/***** MAIN *****/

int main(int argc, char** argv) {
	tree_t tree;
	tree_init(&tree);
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			tree_add_recur(&tree, atoi(argv[i]));
		}
	}
	else {
		tree_add_array(&tree, (int[]) {5, 4, 3, 8, 6}, 5, &tree_add_iter);
	}
	
#define PNL printf("\n")
	tree_print(&tree, "GENERIC", &tree_print_generic); PNL;PNL;
	tree_print(&tree, "BFS", &tree_bfs); PNL;PNL;
	tree_print(&tree, "DFS RECURSIVE", &tree_dfs_recur); PNL;PNL;
	tree_print(&tree, "DFS ITERATIVE", &tree_dfs_iter);
	tree_free(&tree);
	return 0;
}