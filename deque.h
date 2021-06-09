#ifndef deque_H
#define deque_H

typedef struct deque_node {
	void* value;
	struct deque_node* prev;
	struct deque_node* next;
} deque_node_t;

deque_node_t* deque_node_init(void* value);

typedef struct deque {
	int size;
	deque_node_t* head;
	deque_node_t* tail;
} deque_t;

void deque_init(deque_t* deque);
void deque_enqueue(deque_t* deque, deque_node_t* node);
void deque_push(deque_t* deque, deque_node_t* node);
deque_node_t* deque_dequeue(deque_t* deque);
deque_node_t* deque_pop(deque_t* deque);
void deque_free(deque_t* deque);
void deque_print(const deque_t* deque);

#endif