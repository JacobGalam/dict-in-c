#pragma once

#include "node.h"
#include <malloc.h>

typedef struct List
{
	Node* start;
	Node* last;
	int size;
} List;

List* init_list();
void destroy_list(List* list, destroy_data_ptr func);

int add_to_list(List* list, void* value);
void remove_fron_list(List* list, Node* node, destroy_data_ptr func);

Node* first_in_list(List* list);
Node* last_in_list(List* list);

Node* next_in_list(Node* node);
Node* back_in_list(Node* node);

int len_list(List* list);

//// return -1 if list null
//float average_list(List* list);

//// if ptr is not null
//void destory_int(void* ptr);