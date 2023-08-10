#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
matrix *create_matrix(int num_rows, int num_cols)
{
    matrix *tempMatrix = (matrix *)malloc(sizeof(matrix));
    if (tempMatrix == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    tempMatrix->num_rows = num_rows;
    tempMatrix->num_cols = num_cols;

    tempMatrix->data = (int **)malloc(num_rows * sizeof(int *));
    if (tempMatrix->data == NULL) {
        free(tempMatrix); // Clean up previously allocated memory
        return NULL;
    }

    for (int i = 0; i < num_rows; i++) {
        tempMatrix->data[i] = (int *)malloc(num_cols * sizeof(int));
        if (tempMatrix->data[i] == NULL) {
            // Clean up previously allocated memory
            for (int j = 0; j < i; j++) {
                free(tempMatrix->data[j]);
            }
            free(tempMatrix->data);
            free(tempMatrix);
            return NULL;
        }
    }

    return tempMatrix;
}

void add_row(matrix *mat, int *row)
{
    // Add a new row to the matrix and copy over the elements from 'row'
    int new_row = mat->num_rows;
    mat->data = (int **)realloc(mat->data, (new_row + 1) * sizeof(int *));
    mat->data[new_row] = (int *)malloc(mat->num_cols * sizeof(int));

    for (int i = 0; i < mat->num_cols; i++) {
        mat->data[new_row][i] = row[i];
    }

    mat->num_rows++;
}

void add_col(matrix *mat, int *col)
{
    // Add a new column to the matrix and copy over the elements from 'col'
    int new_col = mat->num_cols;
    for (int i = 0; i < mat->num_rows; i++) {
        mat->data[i] = (int *)realloc(mat->data[i], (new_col + 1) * sizeof(int));
        mat->data[i][new_col] = col[i];
    }

    mat->num_cols++;
}

void increment(matrix *mat, int num)
{
    // Increment each value in the matrix by 'num'
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] += num;
        }
    }
}

void scalar_multiply(matrix *mat, int num)
{
    // Multiply each value in the matrix by 'num'
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] *= num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    // Divide each value in the matrix by 'num'
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            mat->data[i][j] /= num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    // Raise each value in the matrix to the power of 'num'
    for (int i = 0; i < mat->num_rows; i++) {
        for (int j = 0; j < mat->num_cols; j++) {
            int original_value = mat->data[i][j];
            for (int k = 1; k < num; k++) {
                mat->data[i][j] *= original_value;
            }
        }
    }
}

void delete_matrix(matrix *mat)
{
    // Deallocate memory for the matrix and its data
    for (int i = 0; i < mat->num_rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}


/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat)
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below


void insert_node_before(chain *chn, int index, matrix *mat) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->mat = mat;

    if (chn->head == NULL) {
        newNode->prev = newNode;
        newNode->next = newNode;
        chn->head = newNode;
    } else {
        node *currentNode = chn->head;

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

void insert_node_after(chain *chn, int index, matrix *mat) {
    index += 1;
    insert_node_before(chn, index, mat);
}

void delete_node(chain *lst, int index) {
    if (lst->head == NULL || index < 0) {
        // Handle invalid cases
        return;
    }

    node *currentNode = lst->head;

    for (int i = 0; i < index && currentNode != NULL; i++) {
        currentNode = currentNode->next;
    }

    if (currentNode == NULL) {
        // Index is out of bounds
        return;
    }

    if (currentNode->prev != NULL) {
        currentNode->prev->next = currentNode->next;
    } else {
        lst->head = currentNode->next; // Update head if deleting the first node
    }

    if (currentNode->next != NULL) {
        currentNode->next->prev = currentNode->prev;
    }

    if (currentNode->mat != NULL) {
        // Free the matrix data if it's allocated
        for (int i = 0; i < currentNode->mat->num_rows; i++) {
            free(currentNode->mat->data[i]);
        }
        free(currentNode->mat->data);
        free(currentNode->mat);
    }

    free(currentNode);
}


void delete_list(chain *chn) {
    node *currentNode = chn->head;

    while (currentNode->next != chn->head) {
        node *temp = currentNode;
        currentNode = currentNode->next;
        delete_matrix(temp->mat);
        free(temp);
    }

    delete_matrix(currentNode->mat);
    free(currentNode);
    chn->head = NULL;
}
