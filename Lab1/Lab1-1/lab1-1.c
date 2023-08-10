// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>
#include <limits.h>

// user-defined header files
#include "node.h"

// macros

#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

// function prototypes
void print_list(list * lst);
void run(list * lst);


int main()
{
    list * lst = (list *) malloc(sizeof(50));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) {
    //printf("Enter comma separated string:\n");
    char data[100];
    scanf(" %[^\n]", data); // Notice the space before %[^\n]

    char newWord[20]; // Corrected: Initialize newWord as an array
    int j = 0;

    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == ',') {
            newWord[j] = '\0'; // Null-terminate the newWord string
            insert_node_after(lst, -1, newWord);
            j = 0; // Reset j for the next word
        } else {
            newWord[j++] = data[i];
        }
    }
    // Insert the last word if it's not empty
    if (j > 0) {
        newWord[j] = '\0'; // Null-terminate the newWord string
        insert_node_after(lst, -1, newWord);
    }

    printf("%s\n", list_to_sentence(lst));

    int command;
    int loop = 1;

    while (loop) {
        scanf("%d", &command);

        switch (command) {
            case 0:
                loop = 0;
                break;
            case INSERT_BEFORE: {
                int index;
                char word[20];
                scanf("%d %s", &index, word);
                insert_node_before(lst, index, word);
                break;
            }
            case INSERT_AFTER: {
                int index;
                char word[20];
                scanf("%d %s", &index, word);
                insert_node_after(lst, index, word);
                break;
            }
            case DELETE_NODE: {
                int index;
                scanf("%d", &index);
                delete_node(lst, index);
                break;
            }
            case DELETE_LIST:
                delete_list(lst);
                loop = 0;
                break;
        }
    }
}



void print_list(list *lst) {
    char *sentence = list_to_sentence(lst);
    if (sentence) {
        printf("%s\n", sentence);
        free(sentence);
    }
}


