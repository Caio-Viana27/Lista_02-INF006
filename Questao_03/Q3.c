#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAM 100
#define TAM_BUFFER 1000

typedef struct _singlylinkednode {
    double num;
    char string[12];
    struct _singlylinkednode* next;
} Singly_linked_node;

typedef struct _singlylinkedlist {
    Singly_linked_node* head;
    Singly_linked_node* tail;
} Singly_linked_list;

typedef struct _Node {
    int num;
    struct _Node* prev;
    struct _Node* next;
    Singly_linked_list* secondary_list;
} Doubly_linked_node;

typedef struct _linkedlist {
    Doubly_linked_node* head;
    Doubly_linked_node* tail;
} Doubly_linked_list;

typedef struct _Multi {
    char* stringNum[TAM];
    int* main_array;
    double* secondary_array;
} Multi;

void init_doubly_linked_list (Doubly_linked_list* list);
void init_singly_linked_list (Singly_linked_list* list);
void create_doubly_linked_Node (Doubly_linked_list* list, int* array, int size);
void create_singly_circular_linked_Node (Singly_linked_list* list, double num, char* string);
char*find_string (char**string, double value);
void insert_main_list (Doubly_linked_list* list, double* array, int size, char**stringNum);
void write_output (Doubly_linked_list* list);
void write_second_list (Singly_linked_list* list);
void insertion_sort (int* array_1, int length1, double* array_2, int length2);
void printArray (int* array_1, int size1, double* array_2, int size2);
void free_stringNum (char**stringNum, int size);
void free_memory (Doubly_linked_list* list);

FILE* file;
FILE* output;

int main() { // L1Q3.in / examples_1.in / examples_2.in
    file = fopen("L1Q3.in", "r");
    if (file == NULL) {
        printf("file failed to open!");
        return 1;
    }
    output = fopen("L1Q3.out", "w+");
    if (file == NULL) {
        printf("output file failed to open!");
        return 1;
    }

    char buffer[TAM_BUFFER];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {

        Doubly_linked_list* main_list = (Doubly_linked_list*) malloc(sizeof(Doubly_linked_list));
        init_doubly_linked_list (main_list);

        char**stringNum = malloc(sizeof(char*) * TAM);
        int*main_array = (int*)malloc(sizeof(int) * TAM);
        double*secondary_array = (double*)malloc(sizeof(double) * TAM);
        int size_stringNum = 0;
        int size_main = 0;
        int size_secondary = 0;

        int i = 0;
        while (buffer[i] != 'I') {
            
            if (buffer[i] >= '0' && buffer[i] <= '9' || buffer[i] == '-') {
                int j = 0;
                char* temp = malloc(sizeof(char) * 12);
                while (buffer[i] != ' ') {
                    temp[j] = buffer[i];
                    temp[j + 1] = '\0';
                    j++;
                    i++;
                }
                main_array[size_main] = atoi(temp);
                size_main++;
                free(temp);
            }
            else i++;
        }
        while (buffer[i] != '\0') {

            if (buffer[i] >= '0' && buffer[i] <= '9' || buffer[i] == '-') {
                int j = 0;
                char* temp = malloc(sizeof(char) * 12);
                while (buffer[i] != ' ' && buffer[i] != '\0' && buffer[i] != '\n') {
                    temp[j] = buffer[i];
                    temp[j + 1] = '\0';
                    j++;
                    i++;
                }
                stringNum[size_stringNum] = malloc(sizeof(char) * 12);
                strcpy(stringNum[size_stringNum], temp);
                size_stringNum++;
                stringNum[size_stringNum] = NULL;
                secondary_array[size_secondary] = atof(temp);
                size_secondary++;
                free(temp);
            }
            else i++;
        }
        insertion_sort(main_array, size_main, secondary_array, size_secondary);
        create_doubly_linked_Node (main_list, main_array, size_main);
        insert_main_list (main_list, secondary_array, size_secondary, stringNum);

        write_output (main_list);
        //free_memory (main_list);
        free(secondary_array);
        free(main_array);
        free_stringNum(stringNum, size_stringNum);
    }
    fclose(file);
    fclose(output);
    return 0;
}

void init_doubly_linked_list (Doubly_linked_list* list) {
    list->head = NULL;
    list->tail = NULL;
}

void init_singly_linked_list (Singly_linked_list* list) {
    list->head = NULL;
    list->tail = NULL;
}

void insertion_sort (int* array_1, int length1, double* array_2, int length2) {

    for (int i = 0; i < length1; i++) {
        int key = array_1[i];
        int j = i - 1;
        while (j >= 0 && array_1[j] > key) {
            array_1[j + 1] = array_1[j];
            j--;
        }
        array_1[j + 1] = key;
    }

    for (int i = 0; i < length2; i++) {
        double key = array_2[i];
        int j = i - 1;
        while (j >= 0 && array_2[j] > key) {
            array_2[j + 1] = array_2[j];
            j--;
        }
        array_2[j + 1] = key;
    }
}

void printArray (int* array_1, int size1, double* array_2, int size2) {
    printf("\n");
    printf("inteiros ");
    for (int i = 0; i < size1; i++) {
        printf("%d ", *(array_1 + i));
    }
    printf("\n");
    printf("floats ");
    for (int i = 0; i < size2; i++) {
        printf("%.2lf ", *(array_2 + i));
    }
    printf("\n");
}

void create_doubly_linked_Node (Doubly_linked_list* list, int* array, int size) {

    for (int i = 0; i < size; i++) {
        
        Doubly_linked_node* new_node = (Doubly_linked_node*) malloc(sizeof(Doubly_linked_node));
        new_node->secondary_list = (Singly_linked_list*) malloc(sizeof(Singly_linked_list));
        new_node->num = array[i];
        init_singly_linked_list (new_node->secondary_list);
    
        if (list->head == NULL) {
            list->head = new_node;
            new_node->prev = NULL;
            list->tail = new_node;
            new_node->next = NULL;
        }
        else {
            list->tail->next = new_node;
            new_node->prev = list->tail;
            new_node->next = NULL;
            list->tail = new_node;
        }
    }
}

void create_singly_circular_linked_Node (Singly_linked_list* list, double value, char* string) {
    Singly_linked_node* new_node = (Singly_linked_node*) malloc(sizeof(Singly_linked_node));
    new_node->num = value;
    strcpy(new_node->string, string);

    if (list->head == NULL) {
        list->tail = list->head = new_node;
        new_node->next = list->head;
    }
    else {
        list->tail->next = new_node;
        new_node->next = list->head;
        list->tail = new_node;
    }
}

char* find_string (char**string, double value) {
    int i = 0;
    while (string[i] != NULL) {
        if (atof(string[i]) == value) {
            return string[i];
        }
        i++;
    }
    return NULL;
}

void insert_main_list (Doubly_linked_list* list, double* array, int size, char**stringNum) {
    Doubly_linked_node* current = (Doubly_linked_node*) malloc(sizeof(Doubly_linked_node));
    current = list->head;

    int i = 0;
    while (current != NULL) {
        for (; i < size; i++) {
            double value = array[i];
            char*string;
            if (find_string(stringNum, value) != NULL) {
                string = find_string(stringNum, value);
            }

           if (value > current->num - 1 && value < current->num + 1) {
                create_singly_circular_linked_Node (current->secondary_list, value, string);
            }
            if (value >= current->num + 1) { break; }
        }
        current = current->next;
    }
    free(current);
}

void write_output (Doubly_linked_list* list) {
    Doubly_linked_node* current = (Doubly_linked_node*) malloc(sizeof(Doubly_linked_node));
    current = list->head;

    fprintf(output, "[");
    while (current != NULL) {
        fprintf(output, "%d", current->num);
        fprintf(output, "(");
        if (current->secondary_list->head != NULL) {
            write_second_list (current->secondary_list);
        }
        fprintf(output, ")");
        if (current->next != NULL) {fprintf(output, "->");}
        current = current->next;
    }
    fprintf(output, "]");
    fprintf(output, "\n");
    free(current);
}

void write_second_list (Singly_linked_list* list) {
    Singly_linked_node* current = (Singly_linked_node*) malloc(sizeof(Singly_linked_node));
    current = list->head;

    bool control = true;
    while (control) {
        fprintf(output, "%s", current->string);
        //fprintf(output, "%.2lf", current->num);
        if (current != list->tail) {fprintf(output, "->");}
        if (current == list->tail) {control = false;}
        current = current->next;
    }
    free(current);
}

// libera a memória alocada

void free_stringNum (char**stringNum, int size) {
    for (int i = 0; i < size; i++) {
        free(stringNum[i]);
    }
}

void free_memory (Doubly_linked_list* list) {

    Doubly_linked_node* current = list->head;
    while (current != NULL) {

        Singly_linked_node* temp = current->secondary_list->head;
        if (temp != NULL) {
            do {
                Singly_linked_node* next = temp->next;
                free(temp);
                temp = next;
            } while (temp != current->secondary_list->tail);
        }
        Doubly_linked_node* next = current->next;
        free(current->secondary_list);
        free(current);
        current = next;
    }
    free(list);
}
