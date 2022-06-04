#define _CRT_SECURE_NO_WARNINGS
#include "BuildHuffmanTree.h"
#include <stdlib.h>
#include <stdio.h>

#define ALPHABET_SIZE 256

Node* get_node(char symb, int isSymb, int freq, Node* left, Node* right) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->symb = symb;
	new_node->isSymb = isSymb;
	new_node->code = malloc(CODE_SIZE);
	new_node->code[0] = '\0';
	new_node->freq = freq;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}

void delete_tree(Node* root) {
	if (!root)
		return;
	delete_tree(root->left);
	delete_tree(root->right);
	free(root->code);
	free(root);
}

Queue* create_queue() {
	Queue* new_queue = (Queue*)malloc(sizeof(Queue));
	new_queue->size = 0;
	new_queue->top = -1;
	new_queue->array = (Node**)malloc(sizeof(Node*)*ALPHABET_SIZE);
	return new_queue;
}

void delete_queue(Queue* q) {
	free(q->array);
	free(q);
}

void push(Queue* q, Node* n) {
	if (q->top == -1)
		q->top = 0;
	q->array[q->size] = n;
	q->size++;
}

void pop(Queue* q) {
	q->top++;
}

Node* top(Queue* q) {
	return(q->array[q->top]);
}


void quick_sort(Queue* q, int left, int right) {
	Node* pivot;
	int l_hold = left, r_hold = right;
	pivot = q->array[left];
	while (left < right) {
		while ((q->array[right]->freq >= pivot->freq) && left < right) {
			right--;
		}
		if (left != right) {
			q->array[left] = q->array[right];
			left++;
		}
		while (q->array[left]->freq <= pivot->freq && left < right) {
			left++;
		}
		if (left != right) {
			q->array[right] = q->array[left];
			right--;
		}
	}
	q->array[left] = pivot;
	int ss = left;
	left = l_hold;
	right = r_hold;
	if (left < ss)
		quick_sort(q, left, ss-1);
	if (right > ss)
		quick_sort(q, ss + 1, right);
}

int size_of_code(char* c) {
	int k = 1;
	for (int i = 0; i < strlen(c); i++) {
		if (c[i] == '\0')
			break;
		k++;
	}
	return k;
}

void node_codding(Node* root) {
	int ind = size_of_code(root->code)-1;
	if (root->left) {
		strcpy(root->left->code, root->code);
		root->left->code[ind] = '0';
		root->left->code[ind + 1] = '\0';
		node_codding(root->left);
	}
	if (root->right) {
		strcpy(root->right->code, root->code);
		root->right->code[ind] = '1';
		root->right->code[ind + 1] = '\0';
		node_codding(root->right);
	}
}

Node* build_huffman_tree(long* freq) {
	Queue* prqueue = create_queue();
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (!freq[i])
			continue;
		Node* new_node = get_node((unsigned char)i, 1, freq[i], NULL, NULL);
		push(prqueue, new_node);
	}
	quick_sort(prqueue, prqueue->top, prqueue->size-1);

	/*for (int i = 0; i < prqueue->size; i++) {
		printf("%c : %d\n", prqueue->array[i]->symb, prqueue->array[i]->freq);
	}*/

	while (prqueue->size - prqueue->top != 1) {
		Node* left_children = prqueue->array[prqueue->top];
		Node* right_children = prqueue->array[prqueue->top + 1];
		int parent_freq = left_children->freq + right_children->freq;
		Node* parent = get_node(' ', 0, parent_freq, left_children, right_children);
		pop(prqueue); pop(prqueue);
		push(prqueue, parent);
		quick_sort(prqueue, prqueue->top, prqueue->size - 1);
	}
	Node* root = top(prqueue);
	delete_queue(prqueue);
	node_codding(root);
	return root;
}