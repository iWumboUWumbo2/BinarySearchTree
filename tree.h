#ifndef TREE_T
#define TREE_T

typedef struct tree_node {
	int value;
	int number;
	struct tree_node* ltNode;
	struct tree_node* rtNode;
	
} tree_node_t;

tree_node_t* tree_node_init(int value);
void tree_node_free(tree_node_t* node);
void tree_node_insert(tree_node_t** root, tree_node_t* node, int* size);
void tree_node_print_generic(const tree_node_t* node);
void tree_node_dfs_recur(const tree_node_t* node, int* visited);

typedef struct tree {
	tree_node_t* root;
	int size;
} tree_t;

void tree_init(tree_t* tree);

void tree_add_recur(tree_t* tree, int value);
void tree_add_iter(tree_t* tree, int value);
void tree_add_array(tree_t* tree, const int* arr, int size, const void (*tree_add) (tree_t*, int));

void tree_print_generic(const tree_t* tree);
void tree_bfs(const tree_t* tree);
void tree_dfs_recur(const tree_t* tree);
void tree_dfs_iter(const tree_t* tree);

void tree_free(tree_t* tree);
void tree_print(const tree_t* tree, const char* printer, const void (*tree_printer) (const tree_t*));

#endif