#define _CRT_SECURE_NO_WARNINGS
#include "Decode.h"
#include "BuildHuffmanTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE* enf;
FILE* dnf;
FILE* tbl;

#define CODE_SIZE 256
#define ALPHABET_SIZE 256

NODE* create_node(unsigned char symb, unsigned char isSymb, NODE* left, NODE* right) {
	NODE* new_node = (NODE*)malloc(sizeof(NODE));
	new_node->isSymb = isSymb;
	new_node->symb = symb;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}

void print_in_def(Node* root, int length) {
	Node* currentroot = root;
	for (int i = 0; i < length; i+=8) {
		unsigned char symb = (unsigned char)fgetc(enf);
		for (int j = 7; j >= 0 && i + 7 - j < length; j--) {
			char character = (symb >> j) & 1;
			if (character == 0) {
				currentroot = currentroot->left;
			}
			else {
				currentroot = currentroot->right;
			}
			if (currentroot->isSymb) {
				fprintf(dnf, "%c", currentroot->symb);
				currentroot = root;
			}
		}
	}
}

void decode(Node* binarytreeroot) {
	enf = fopen("encodefile.txt", "rb");
	dnf = fopen("decodefile.txt", "w");
	tbl = fopen("table.txt", "r");

	fseek(enf, 0L, SEEK_END);
	long enflen = ftell(enf);
	fseek(enf, 0, SEEK_SET);
	char cstrlen[256];
	fgets(cstrlen, 256, enf);
	int length = atoi(cstrlen);


	NODE* root = create_node(0, 0, NULL, NULL);

	print_in_def(binarytreeroot, length);

	free(root);
	fclose(dnf); fclose(enf); fclose(tbl);
}