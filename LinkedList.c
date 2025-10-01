/*
 * LinkedList.c
 * This file contains all functions for creating, modifying, and managing a linked list
 */

#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Creates a new node with a deep copy of the given data
 */
struct Node* createNode(char* data) {
    // Check for NULL input
    if (data == NULL) {
        return NULL;
    }

    // Allocate memory for new Node struct
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        // Memory allocation failed
        return NULL;
    }

    // Allocate memory for character data (string)
    newNode->data = (char*)malloc((strlen(data) + 1) * sizeof(char));
    if (newNode->data == NULL) {
        // Memory allocation for data failed, free the node
        free(newNode);
        return NULL;
    }

    // Copy the string data to newly allocated memory
    strcpy(newNode->data, data);

    // Initialize next pointer to NULL (single node)
    newNode->next = NULL;

    return newNode;
}

/*
 * Insert a node at the end of the linked list
 * Handle both empty list and non-empty list cases
 */
void insertAtEnd(struct Node** head, struct Node* newNode) {
    // Check for NULL parameters
    if (head == NULL || newNode == NULL) {
        return;
    }
    
    // If list is empty, new node becomes the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    // Traverse to the end of the list
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Append new node at the end
    current->next = newNode;
}

/*
 * Create a linked list from file contents
 */
struct Node* createList(FILE* inf) {
    // Check for NULL file pointer
    if (inf == NULL) {
        return NULL;
    }
    
    struct Node* head = NULL;
    char fileLine[MAX_LINE_LENGTH];

    while (fgets(fileLine, MAX_LINE_LENGTH, inf) != NULL) {
        // Remove trailing newline character
        fileLine[strcspn(fileLine, "\n")] = 0;

        struct Node* newNode = createNode(fileLine);
        if (newNode != NULL) {
            // Insert node at the end of the list
            insertAtEnd(&head, newNode);
        }
    }
    return head;
}

/*
 * Remove a node at the specified index from the linked list
 */
struct Node* removeNode(struct Node** head, int index) {
    // Check for NULL parameters and negative index
    if (head == NULL || *head == NULL || index < 0) {
        return NULL;
    }

    struct Node* current = *head;
    struct Node* previous = NULL;
    
    // Special case: removing head node (index 0)
    if (index == 0) {
        *head = current->next;
        current->next = NULL;  // Disconnect from list
        return current;
    }

    // Traverse to the node at specified index
    int currentIndex = 0;
    while (current != NULL && currentIndex < index) {
        previous = current;
        current = current->next;
        currentIndex++;
    }

    // Check if we've gone past the end of the list
    if (current == NULL) {
        return NULL;
    }

    // Remove node from list
    previous->next = current->next;
    current->next = NULL;  // Disconnect from list
    
    return current;
}

/*
 * Traverses and prints all nodes in the list
 * Prints each node's data on a new line
 */
void traverse(struct Node* head) {
    struct Node* current = head;
    
    // Traverse through entire list
    while (current != NULL) {
        // Print current node's data
        printf("%s\n", current->data);
        // Move to next node
        current = current->next;
    }
}

/*
 * Frees memory for a single node
 */
void freeNode(struct Node* aNode) {
    // Check for NULL node
    if (aNode == NULL) {
        return;
    }
    
    // Free the character data first
    if (aNode->data != NULL) {
        free(aNode->data);
    }
    
    // Free the Node struct itself
    free(aNode);
}

/*
 * Frees memory for entire linked list
 * Traverses list and frees each node
 */
void freeList(struct Node** head) {
    // Check for NULL parameters
    if (head == NULL || *head == NULL) {
        return;
    }
    
    struct Node* current = *head;
    struct Node* nextNode = NULL;
    
    // Traverse and free each node
    while (current != NULL) {
        nextNode = current->next;  // Save next node before freeing
        freeNode(current);          // Free current node
        current = nextNode;         // Move to next node
    }
    
    // Set head pointer to NULL
    *head = NULL;
}
