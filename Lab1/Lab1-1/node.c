// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:

size_t strlcpy(char *dst, const char *src, size_t size) {
    size_t src_len = strlen(src);
    size_t copy_len = src_len < size - 1 ? src_len : size - 1;
    memcpy(dst, src, copy_len);
    dst[copy_len] = '\0';
    return src_len;
}

size_t strlcat(char *dst, const char *src, size_t size) {
    size_t dst_len = strlen(dst);
    size_t src_len = strlen(src);
    size_t copy_len = size - dst_len - 1;
    if (src_len < copy_len) {
        copy_len = src_len;
    }
    memcpy(dst + dst_len, src, copy_len);
    dst[dst_len + copy_len] = '\0';
    return dst_len + src_len;
}



// implementation
void insert_node_before(list *lst, int index, char *word) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->word = (char *)malloc(strlen(word) + 1);
    strlcpy(newNode->word, word, strlen(word) + 1); // Corrected strlcpy usage

    if (lst->head == NULL) {
        newNode->prev = newNode;
        newNode->next = newNode;
        lst->head = newNode;
    } else {
        node *currentNode = lst->head;

        if (index >= 0) {
            for (int i = 0; i < index; i++) {
                currentNode = currentNode->next;
            }
        } else if (index < 0) {
            for (int i = 0; i > index; i--) {
                currentNode = currentNode->prev;
            }
        }
        
        newNode->prev = currentNode->prev;
        newNode->next = currentNode;
        currentNode->prev->next = newNode;
        currentNode->prev = newNode;
        

    }
}



void insert_node_after(list *lst, int index, char *word) {
    index+=1;
    insert_node_before(lst, index, word);
}


char *list_to_sentence(list *lst) {
    if (lst->head == NULL) {
        return NULL;  // Handle the case of an empty list
    }

    node *currentNode = lst->head;
    int totalLength = 0;
    int wordCount = 0;

    // Calculate the total length needed for the sentence
    do {
        totalLength += strlen(currentNode->word) + 1; // +1 for the space
        wordCount++;
        currentNode = currentNode->next;
    } while (currentNode != lst->head);

    // Allocate memory for the sentence
    char *sentence = (char *)malloc(totalLength + 1); // +1 for the null terminator

    if (sentence == NULL) {
        perror("Memory allocation error");
        return NULL;
    }

    sentence[0] = '\0';  // Initialize the sentence as an empty string

    currentNode = lst->head;

    // Construct the sentence in order
    for (int i = 0; i < wordCount; i++) {
        strlcat(sentence, currentNode->word, totalLength + 1); // Concatenate the word
        strlcat(sentence, " ", totalLength + 1); // Concatenate a space
        currentNode = currentNode->next;
    }

    // Remove the trailing space
    if (strlen(sentence) > 0) {
        sentence[strlen(sentence) - 1] = '\0'; // Remove the last space
    }

    return sentence;
}


void delete_node(list *lst, int index) {
    if (lst->head == NULL) {
        // Handle deletion from an empty list
        return;
    }


    node *currentNode = lst->head;

    if (index >= 0) {
        for (int i = 0; i < index; i++) {
            currentNode = currentNode->next;
        }
    } else if (index < 0) {
        for (int i = 0; i > index; i--) {
            currentNode = currentNode->prev;
        }
    }

    if (currentNode->next == currentNode) {
        // Only one node in the list
        lst->head = NULL;
    } else {
        currentNode->prev->next = currentNode->next;
        currentNode->next->prev = currentNode->prev;

        if (currentNode == lst->head) {
            lst->head = currentNode->next; // Update start pointer if deleting the first node
        }
    }

    free(currentNode->word);
    free(currentNode);
}

void delete_list(list *lst) {
    node *currentNode = lst->head;

    while (currentNode->next != lst->head) {
        node *temp = currentNode;
        currentNode = currentNode->next;
        free(temp->word);
        free(temp);
    }

    free(currentNode->word);
    free(currentNode);
    lst->head = NULL;
}
