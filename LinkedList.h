/*
 * LinkedList.h
 * Header file for singly linked list implementation
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Givens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Creates a new Node with the given data
 * Parameters:
 *   data - character array to store in the node
 * Returns:
 *   Pointer to the newly created Node
 */
struct Node* createNode(char* data);

/*
 * Inserts a node at the end of the linked list
 * Parameters:
 *   head - pointer to pointer to the head of the list
 *   newNode - node to insert at the end
 */
void insertAtEnd(struct Node** head, struct Node* newNode);

/*
 * Creates a linked list from file contents (line by line)
 * Parameters:
 *   inf - pointer to an opened file
 * Returns:
 *   Pointer to the head of the newly created list
 */
struct Node* createList(FILE* inf);

/*
 * Removes a node at the specified index from the list
 * Parameters:
 *   head - pointer to pointer to the head of the list
 *   index - index of the node to remove (0-based)
 * Returns:
 *   Pointer to the removed node, or NULL if operation fails
 */
struct Node* removeNode(struct Node** head, int index);

/*
 * Traverses the list and prints each node's data
 * Parameters:
 *   head - pointer to the head of the list
 */
void traverse(struct Node* head);

/*
 * Frees memory allocated for a single node
 * Parameters:
 *   aNode - pointer to the node to free
 */
void freeNode(struct Node* aNode);

/*
 * Frees memory for the entire linked list
 * Parameters:
 *   head - pointer to pointer to the head of the list
 */
void freeList(struct Node** head);

#endif
