#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Givens.h"
#include <stdio.h>

// Function prototypes

// creates a new linked list node with a copy of given string
struct Node* createNode(char* data);

// Appends a node to the end of the list
void insertAtEnd(struct Node** head, struct Node* newNode);

// reads input file line by line, creates full linked list
struct Node* createList(FILE* inf);

// Removes node at given index (0-based). Returns removed node or NULL
struct Node* removeNode(struct Node** head, int index);

// traverses and prints all nodes' data
void traverse(struct Node* head);

// frees memory for a single node (data + struct)
void freeNode(struct Node* aNode);

// frees memory for the entire linked list, sets head to NULL
void freeList(struct Node** head);

#endif
