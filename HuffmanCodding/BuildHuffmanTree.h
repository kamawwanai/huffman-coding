#pragma once
#include <string.h>

#define CODE_SIZE 256

typedef struct node{
	unsigned char symb;
	int isSymb;
	unsigned int freq;
	char* code;
	struct node* left, * right;
}Node;

typedef struct queue{
	Node** array;
	int size;
	int top;
}Queue;

Node* get_node(char symb, int isSymb, int freq, Node* left, Node* right);
void delete_tree(Node* root);

Queue* create_queue();
void delete_queue(Queue* q);
void push(Queue* q, Node* n);
void pop(Queue* q);
Node* top(Queue* q);

void quick_sort(Queue* q, int left, int right);
int size_of_code(char* c);
void node_codding(Node* root);
Node* build_huffman_tree(long* freq);