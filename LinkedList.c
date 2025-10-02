/*
 * LinkedList.c
 * Implementation of singly linked list functions
 */

#include "LinkedList.h"

/*
 * Creates a new Node with the given data
 * Allocates memory for both the Node and a copy of the data string
 */
struct Node* createNode(char* data) {
    // Allocate memory for the new Node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    // Check if allocation was successful
    if (newNode == NULL) {
        return NULL;
    }
    
    // Allocate memory for the data string (including null terminator)
    newNode->data = (char*)malloc(strlen(data) + 1);
    
    // Check if allocation was successful
    if (newNode->data == NULL) {
        free(newNode);
        return NULL;
    }
    
    // Copy the data into the newly allocated string
    strcpy(newNode->data, data);
    
    // Initialize next pointer to NULL (single node, not yet in a list)
    newNode->next = NULL;
    
    return newNode;
}

/*
 * Inserts a node at the end of the linked list
 * Handles empty lists and updates head pointer if necessary
 */
void insertAtEnd(struct Node** head, struct Node* newNode) {
    // Check if head pointer itself is NULL
    if (head == NULL) {
        return;
    }
    
    // If the list is empty, newNode becomes the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    // Traverse to the last node in the list
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Insert newNode at the end
    current->next = newNode;
}

/*
 * Creates a linked list from file contents
 * Reads file line by line and creates a node for each line
 */
struct Node* createList(FILE* inf) {
    // Check if file pointer is NULL
    if (inf == NULL) {
        return NULL;
    }
    
    struct Node* head = NULL;
    char fileLine[MAX_LINE_LEN];
    
    // Read file line by line
    while (fgets(fileLine, MAX_LINE_LEN, inf) != NULL) {
        // Remove trailing newline character
        fileLine[strcspn(fileLine, "\n")] = 0;
        
        // Create a new node with the line data
        struct Node* newNode = createNode(fileLine);
        
        // Check if node creation was successful
        if (newNode == NULL) {
            // Free any nodes created so far before returning
            freeList(&head);
            return NULL;
        }
        
        // Insert the new node at the end of the list
        insertAtEnd(&head, newNode);
    }
    
    return head;
}

/*
 * Removes a node at the specified index from the list
 * Returns pointer to the removed node (caller must free it)
 */
struct Node* removeNode(struct Node** head, int index) {
    // Edge case: head pointer is NULL
    if (head == NULL) {
        return NULL;
    }
    
    // Edge case: list is empty
    if (*head == NULL) {
        return NULL;
    }
    
    // Edge case: negative index
    if (index < 0) {
        return NULL;
    }
    
    struct Node* removedNode = NULL;
    
    // Special case: removing the head node (index 0)
    if (index == 0) {
        removedNode = *head;
        *head = (*head)->next;
        removedNode->next = NULL; // Disconnect from list
        return removedNode;
    }
    
    // Traverse to the node before the one to remove
    struct Node* current = *head;
    int currentIndex = 0;
    
    // Move to the node just before the target index
    while (current->next != NULL && currentIndex < index - 1) {
        current = current->next;
        currentIndex++;
    }
    
    // Edge case: index out of bounds
    if (current->next == NULL) {
        return NULL;
    }
    
    // Remove the node at the target index
    removedNode = current->next;
    current->next = removedNode->next;
    removedNode->next = NULL; // Disconnect from list
    
    return removedNode;
}

/*
 * Traverses the list and prints each node's data
 * Prints each node's data on a separate line
 */
void traverse(struct Node* head) {
    struct Node* current = head;
    
    // Traverse the entire list
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

/*
 * Frees memory allocated for a single node
 * Frees both the data string and the node itself
 */
void freeNode(struct Node* aNode) {
    // Check if node pointer is NULL
    if (aNode == NULL) {
        return;
    }
    
    // Free the dynamically allocated data string
    if (aNode->data != NULL) {
        free(aNode->data);
    }
    
    // Free the node itself
    free(aNode);
}

/*
 * Frees memory for the entire linked list
 * Iterates through all nodes and frees them
 */
void freeList(struct Node** head) {
    // Check if head pointer itself is NULL
    if (head == NULL) {
        return;
    }
    
    struct Node* current = *head;
    struct Node* nextNode = NULL;
    
    // Traverse and free each node
    while (current != NULL) {
        nextNode = current->next;
        freeNode(current);
        current = nextNode;
    }
    
    // Set head to NULL to indicate empty list
    *head = NULL;
}
