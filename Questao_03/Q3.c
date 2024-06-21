#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _singlylinkednode {
    double num;
    struct _singlylinkednode* next;
} Singly_linked_node;

typedef struct _singlylinkedlist {
    Singly_linked_node* head;
    Singly_linked_node* tail;
} Singly_linked_list;

typedef struct _Node {
    struct _Node* prev;
    struct _Node* next;
    int num;
    Singly_linked_list* secondary_list;
} Doubly_linked_node;

typedef struct _linkedlist {
    Doubly_linked_node* head;
    Doubly_linked_node* tail;
} Doubly_linked_list;


void init_doubly_linked_list (Doubly_linked_list* list);
void init_singly_linked_list (Singly_linked_list* list);
void create_singly_linked_list (Singly_linked_list* list, double num);
void create_doubly_linked_Node (Doubly_linked_list* list, int num);
void create_singly_circular_linked_Node (Singly_linked_list* list, double num);
void insert_main_list (Doubly_linked_list* list, double value);

int main() {
    Doubly_linked_list* main_list = (Doubly_linked_list*) malloc(sizeof(Doubly_linked_list));
    init_doubly_linked_list (main_list);

    FILE* file = fopen("L1Q3.in", "r");
    if (file == NULL) {
        printf("file failed to open!");
        return 1;
    }
    // LE 10 9 6 4 LI 4.11 10.1 6.88 4.99 9.3 9.2 6.15 4.33 INPUT
    // [4(4.11->4.33->4.99)->6(6.15->6.88)->9(9.2->9.3)->10(10.1)] OUTPUT
    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {

        int i = 0;
        while (buffer[i] != 'i') {
            
            if (buffer[i] >= '0' && buffer[i] <= '9') {
                int j = 0;
                char temp[10];
                while (buffer[i] != ' ') {
                    temp[j] = buffer[i];
                    temp[j + 1] = '\0';
                    j++;
                    i++;
                }
                create_doubly_linked_Node (main_list, atoi(temp));
            }
            else i++;
        }
        while (buffer[i] != '\0') {

            if (buffer[i] >= '0' && buffer[i] <= '9') {
                int j = 0;
                char temp[10];
                while (buffer[i] != ' ' && buffer[i] != '\0') {
                    temp[j] = buffer[i];
                    temp[j + 1] = '\0';
                    j++;
                    i++;
                }
                double temp_num = atof(temp);
            }
            else i++;
        }
    }
    fclose(file);
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

void create_singly_linked_list (Singly_linked_list* list, double num) {
    Singly_linked_list* singly_linked_list = (Singly_linked_list*) malloc(sizeof(Singly_linked_list));


}

void create_doubly_linked_Node (Doubly_linked_list* list, int num) {
    Doubly_linked_node* new_node = (Doubly_linked_node*) malloc(sizeof(Doubly_linked_node));
    init_singly_linked_list (new_node->secondary_list);
    new_node->num = num;

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

void create_singly_circular_linked_Node (Singly_linked_list* list, double num) {
    Singly_linked_node* new_node = (Singly_linked_node*) malloc(sizeof(Singly_linked_node));
    new_node->num = num;

    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
        new_node->next = list->head;
    }
    else {
        list->tail->next = new_node;
        new_node->next = list->head;
        list->tail = new_node;
    }
}

void insert_main_list (Doubly_linked_list* list, double value) {
    Doubly_linked_node* current = (Doubly_linked_node*) malloc(sizeof(Doubly_linked_node));
    current = list->head;

    while (current != NULL) {
        if (value > current->num && value < current->num + 1) {
            create_singly_linked_list (current->secondary_list, value);
        }
        current = current->next;
    }
}