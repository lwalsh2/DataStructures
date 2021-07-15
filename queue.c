/*
 * Queue Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>

// Declares queue node struct.
typedef struct queue_node_ {
  // Data of queue node
  int number;
  // The next node added to queue
  struct queue_node_ * next;
} queue_node;

// Declares queue struct. (holds last node)
typedef struct queue_ {
  // The first and last node of the list
  queue_node * front;
  queue_node * back;
} queue;

// Allocates node with the given data, and returns address.
queue_node * create_node(int number) {
	// Allocate data for node, setting values to NULL/0.
	queue_node * node = calloc(1, sizeof(node));
	// Set the node's data
	node->number = number;
	return node;
}

// Allocates list with the given head, and returns address.
queue * create_queue(queue_node * head) {
	// Allocate list.
	queue * list = malloc(sizeof(queue));
	// Set the head of the list.
	list->front = head;
  list->back = head;
	return list;
}

// Append node to front of list. (Replaces head node)
int push_node(queue_node * new, queue * list) {
	// Makes sure there is a list and node to append.
	if (!list || !new) {
		return 0;
	}
	// If the list is empty, sets the node as head.
	if (!list->front) {
    list->front = new;
		list->back = new;
	}
	// Replaces the current head of the list.
	else {
    list->back->next = new;
		list->back = new;
	}
	return 1;
}

// Frees head node of queue.
void pull_node(queue * list) {
	if (!list || !list->front) {
		return;
	}
	// pull the head
	queue_node *temp = list->front;
	if (list->front->next) {
		list->front = list->front->next;
	}
	else {
		list->front = NULL;
    list->back = NULL;
	}
	free(temp);
}

// Frees nodes and sets head to NULL.
int empty_queue(queue * list) {
	// Verify there's a list
	if (!list) {
		return 0;
	}
	// Free any nodes attached to the list.
	while (list->front) {
		pull_node(list);
	}
	// Empties list by setting to NULL.
	list = NULL;
	return 1;
}

// Prints the front of the queue.
void peek_node(queue * list) {
	printf("Printing front: \n");
	if (!list || !list->front) {
		printf("   No queue, head empty\n");
		return;
	}
	printf("   front's int = %d\n", list->front->number);
}

int main()
{
  printf("Creating queue:\n");
	queue * list = create_queue(create_node(3));
  peek_node(list);
	if (!push_node(create_node(1), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);
	if (!push_node(create_node(2), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);
	pull_node(list);
  peek_node(list);
	if (!push_node(create_node(1), list)) {
		printf("Push failed.\n");
	}
  peek_node(list);

	printf("Deleting queue:\n");
	if (!empty_queue(list)) {
		printf("Empty queue failed.\n");
	}
	peek_node(list);
	free(list);
  return 0;
}
