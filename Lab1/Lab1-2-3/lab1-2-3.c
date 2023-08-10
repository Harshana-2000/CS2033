// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.h"

#define MAX_COLS 10

// function prototypes
void print_chain(chain * chn);
void run(chain * chn);
matrix *clone(matrix *src);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
/*    for (int i = 0; i < 5; i++) {
        matrix *mat = create_matrix(2, 2);
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                mat->data[j][k] = (i + 1) * 10 + (j + 1) * (k + 1);
            }
        }
        insert_node_before(chn, i, mat);
    } */
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

// parse the input
void run(chain *chn)
{
    int row;
    printf("rows : ");
    scanf("%d", &row);

    int *first_row = (int *)malloc(MAX_COLS * sizeof(int));
    int column = 0;
    do {
        scanf("%d", &first_row[column++]);
    } while (getchar() != '\n' && column < MAX_COLS);
    first_row = (int *)realloc(first_row, column * sizeof(int)); // Resize the array to the actual number of elements

    printf("first column done!\n");
    matrix *currentMat = create_matrix(row, column);
    for (int i = 0; i < column; i++) {
        currentMat->data[0][i] = first_row[i];
    }
    free(first_row);

    for (int j = 1; j < row; j++) {
        currentMat->data[j] = (int *)malloc(column * sizeof(int)); // Allocate memory for the row
        int count = 0;
        do {
            scanf("%d", &currentMat->data[j][count++]);
        } while (getchar() != '\n' && count < column);

        printf("row done!\n");
    }

    
    node * currentNode;
    insert_node_after(chn,-1,currentMat);
    currentNode = chn->head;

    int loop = 1;
    int command;
    while (loop) {
        printf("command : ");
        scanf("%d", &command);

        switch (command) {
            case 0:
                loop = 0;
                break;
            case 1:
                break;
            case 2: {
                int new_row[currentNode->mat->num_cols];
                for (int i = 0; i < currentNode->mat->num_cols; i++) {
                    scanf("%d ", &new_row[i]);
                }
                matrix *mat = clone(currentNode->mat);
                add_row(mat, new_row);
                node *newNode = (node *)malloc(sizeof(node));
                newNode->mat = mat;
                insert_node_after(chn, -1, mat);
                currentNode = currentNode->next;
                break;
            }
            case 3: {
                int new_col[currentNode->mat->num_rows];
                for (int i = 0; i < currentNode->mat->num_rows; i++) {
                    scanf("%d", &new_col[i]);
                }
                matrix *mat = clone(currentNode->mat);
                add_col(mat, new_col);
                node *newNode = (node *)malloc(sizeof(node));
                newNode->mat = mat;
                insert_node_before(chn, 0, mat);
                currentNode = currentNode->next;
                break;
            }
            case 4: {
                matrix *mat = clone(currentNode->mat);
                int inc ;
                scanf("%d", &inc);
                increment(mat, inc);
                node *newNode = (node *)malloc(sizeof(node));
                newNode->mat = mat;
                insert_node_before(chn, 0, mat);
                currentNode = currentNode->next;
                break;
            }
            case 5: {
                int multiplier;
                scanf("%d", &multiplier);
                matrix *mat = clone(currentNode->mat);
                scalar_multiply(mat, multiplier);
                node *newNode = (node *)malloc(sizeof(node));
                newNode->mat = mat;
                insert_node_before(chn, 0, mat);
                currentNode = currentNode->next;
                break;
            }
            case 6: {
                int divisor;
                scanf("%d", &divisor);
                matrix *mat = clone(currentNode->mat);
                scalar_divide(mat, divisor);
                node *newNode = (node *)malloc(sizeof(node));
                newNode->mat = mat;
                insert_node_before(chn, 0, mat);
                currentNode = currentNode->next;
                break;
            }
            case 7: {
                int power;
                scanf("%d", &power);
                matrix *mat = clone(currentNode->mat);
                scalar_power(mat, power);
                node *newNode = (node *)malloc(sizeof(node));
                newNode->mat = mat;
                insert_node_before(chn, 0, mat);
                currentNode = currentNode->next;
                break;
            }
            case 8: {
                matrix *mat = clone(currentNode->mat);
                delete_matrix(mat);
                node *newNode = (node *)malloc(sizeof(node));
                newNode->mat = mat;
                insert_node_before(chn, 0, mat);
                currentNode = currentNode->next;
                //loop = 0;
                break;
            }
            default:{
                loop = 0;
                break;}
        }
    }
}




// Print the chain of matrices
void print_chain(chain *chn)
{
    node *currentNode = chn->head;
    while (currentNode->next != chn->head) {
        print_matrix(currentNode->mat);
        printf("\n");
        currentNode = currentNode->next;
    }
    print_matrix(currentNode->mat); // Print the last matrix
}

matrix *clone(matrix *src)
{
    matrix *newMat = create_matrix(src->num_rows, src->num_cols);
    for (int i = 0; i < src->num_rows; i++) {
        for (int j = 0; j < src->num_cols; j++) {
            newMat->data[i][j] = src->data[i][j];
        }
    }
    return newMat;
}

