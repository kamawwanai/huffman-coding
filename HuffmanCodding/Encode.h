#pragma once

#include "BuildHuffmanTree.h"
#include <string.h>

char** create_table();
void delete_table(char** table);

void get_table_code(char** table, int* table_size);

void print_code_table(char** table);
//void print_code_str(Node* root, char* str, char** table);
char* get_code_str(Node* root, char* str, char** table);

void encode(Node* root, char* str);