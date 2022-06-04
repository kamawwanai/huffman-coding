#define _CRT_SECURE_NO_WARNINGS

#include "BuildHuffmanTree.h"
#include "Encode.h"
#include <stdio.h>
#include <stdlib.h>

#define CODE_SIZE 256
#define ALPHABET_SIZE 256

int main() {
	FILE* fr = fopen("file1.txt", "rb");
	if (!fr) {
		return 0;
	}
	int* freq=(int*)calloc(ALPHABET_SIZE,sizeof(int));
	fseek(fr, 0L, SEEK_END);
	long length = ftell(fr);
	fseek(fr, 0, SEEK_SET);
	char* str =(char*)calloc(length+1,sizeof(char));
	for (int i = 0; i < length; i++){
		char el = fgetc(fr);
		freq[(unsigned char)el]++;
		str[i] = (unsigned char)el;
	}
	fclose(fr);
	str[length] = '\0';
	Node* root=build_huffman_tree(freq);
	free(freq);
	encode(root, str);
	decode(root);
	delete_tree(root);
	free(str);
	return 0;
}