#pragma once
#include "BuildHuffmanTree.h"

typedef struct nodde {
	unsigned char symb;
	unsigned char isSymb;
	struct nodde* left,* right;
}NODE;

void decode(Node* binarytreeroot);