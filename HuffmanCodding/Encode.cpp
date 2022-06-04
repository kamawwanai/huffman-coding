#define _CRT_SECURE_NO_WARNINGS
#include "Encode.h"
#include "BuildHuffmanTree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 256

FILE* enf;

unsigned char** create_table() {
	unsigned char** table = (unsigned char**)calloc(ALPHABET_SIZE,sizeof(unsigned char*));
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		table[i] = (unsigned char*)calloc(CODE_SIZE + 1,sizeof(unsigned char));
	}
	return table;
}

void delete_table(unsigned char** table) {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		free(table[i]);
	}
	free(table);
}

void get_table_code(Node* root, unsigned char** table) {
	if (!root)
		return;
	if (root->isSymb) {
		strcpy(table[(unsigned char)root->symb],root->code);
	}
	get_table_code(root->right, table);
	get_table_code(root->left, table);
}

void print_code_table(unsigned char** table) {
	FILE* tb = fopen("table.txt", "w");
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (table[i][0] != '\0')
			fprintf(tb, "%c%s\n", (unsigned char)i, table[i]);
	}
	fclose(tb);
}

//void print_code_str(Node* root, unsigned char* str, unsigned char** table) {
//	int len = strlen(str);
//	for (int i = 0; i < len; i++) {
//		fprintf(enf,"%s", table[str[i]]);
//	}
//}

unsigned char* get_code_str(unsigned char* str, unsigned char** table) {
	int len = strlen(str);
	unsigned char* cstr = (unsigned char*)calloc(len * 256, sizeof(unsigned char*));
	int cstr_size = 0, capacity = len * 256;
	for (int i = 0; i < len; i++) {
		if (cstr_size == capacity) {
			cstr = (unsigned char*)realloc(cstr, capacity * 2);
			capacity *= 2;
		}
		unsigned char* getcode = table[(unsigned)str[i]];
		if (!getcode) {
			continue;
		}
		int getcodelen = strlen(getcode);
		for (int i = 0; i < getcodelen; i++) {
			cstr[cstr_size] = getcode[i];
			cstr_size++;
		}
	}
	return cstr;
}

void dump_cstr_bits(unsigned char* cstr) {
	int len = strlen(cstr);
	unsigned char cur_byte = 0;
	for (int i = 0; i < len; i+=8) {
		for (int j = 7; (j >= 0) && (i + (7 - j) < len); --j) {
			cur_byte += (cstr[i+(7-j)] - '0') << j;
		}
		fputc(cur_byte, enf);
		cur_byte = 0;
	}
}

void print_cstr(unsigned char* cstr) {
	int len = strlen(cstr);
	for (int i = 0; i < len; ++i) {
		if (i % 8 == 0) {
			putc(' ', stdout);
		}
		putc(cstr[i], stdout);
	}
}


void encode(Node* root, unsigned char* str) {
	enf = fopen("encodefile.txt", "wb");

	unsigned char** table = create_table();
	get_table_code(root, table);
	print_code_table(table);

	unsigned char* cstr = get_code_str(str, table);
	fprintf(enf, "%d\n", strlen(cstr));
	dump_cstr_bits(cstr);
	//fputc("\r\n", enf);
	printf("%s", cstr);

	delete_table(table);
	free(cstr);
	fclose(enf);
}