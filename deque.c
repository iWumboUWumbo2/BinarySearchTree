#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

/***** NODE *****/

deque_node_t* deque_node_init(void* value) {
	if (value == NULL) 
		return NULL;
	
	deque_node_t* node = malloc(sizeof(deque_node_t));
	node->value = value;
	node->prev = node->next = NULL;
	return node;
}

/***** deque *****/

void deque_init(deque_t* deque) {
	deque->size = 0;
	deque->head = deque->tail = NULL;
}

void deque_enqueue(deque_t* deque, deque_node_t* node) {	
	if (deque->head == NULL || deque->tail == NULL) {
		deque->head = deque->tail = node;
		deque->size++;
		return;
	}
	
	node->prev = deque->tail;
	deque->tail->next = node;
	deque->tail = node;
	deque->size++;
}

void deque_push(deque_t* deque, deque_node_t* node) {
	deque_enqueue(deque, node);
}

deque_node_t* deque_dequeue(deque_t* deque) {
	if (deque->head == NULL || deque->tail == NULL) {
		return NULL;
	}
	deque_node_t* node = deque->head;
	deque->head = deque->head->next;
	node->next = NULL;
	
	if (deque->head == NULL || deque->tail == NULL)
		deque->head = deque->tail = NULL;
	else
		deque->head->prev = NULL;

	deque->size--;
	return node;
}

deque_node_t* deque_pop(deque_t* deque) {
	if (deque->head == NULL || deque->tail == NULL) {
		return NULL;
	}
	deque_node_t* node = deque->tail;
	deque->tail = deque->tail->prev;
	node->prev = NULL;
	
	if (deque->head == NULL || deque->tail == NULL)
		deque->head = deque->tail = NULL;
	else
		deque->tail->next = NULL;
	
	deque->size--;
	return node;
}

void deque_free(deque_t* deque) {
	if (deque->head == NULL || deque->tail == NULL) {
		return;
	}
	
	deque_node_t* ptr = deque->head;
	deque_node_t* prev;
	
	while (ptr != NULL) {
		prev = ptr;
		ptr = ptr->next;
		free(prev);
	}
	
	deque_init(deque);
}

void deque_print(const deque_t* deque) {
	printf("deque: ");
	if (deque->head != NULL && deque->tail != NULL) {
		deque_node_t* ptr = deque->head;
		while (ptr != NULL) {
			printf("%d ", ptr->value);
			ptr = ptr->next;
		}	
	}
	printf("\nSize: %d\n", deque->size);
}

/***** MAIN *****/
/*
int main(int argc, char** argv) {
	deque_t deque;
	deque_init(&deque);
	deque_enqueue_array(&deque, (int[]) {5, 6}, 2);
	deque_print(&deque);
	deque_node_t* node = deque_dequeue(&deque);
	printf("%d\n", node->value);
	deque_print(&deque);
	node = deque_dequeue(&deque);
	printf("%d\n", node->value);
	deque_print(&deque);
	deque_free(&deque);
	return 0;
}
*/
