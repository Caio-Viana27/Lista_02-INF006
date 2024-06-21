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
    int num;
    struct _Node* prev;
    struct _Node* next;
    Singly_linked_list* secondary_list;
} Doubly_linked_node;

typedef struct _linkedlist {
    Doubly_linked_node* head;
    Doubly_linked_node* tail;
} Doubly_linked_list;


void init_doubly_linked_list (Doubly_linked_list* list);
void init_singly_linked_list (Singly_linked_list* list);
void create_doubly_linked_Node (Doubly_linked_list* list, int num);
void create_singly_circular_linked_Node (Singly_linked_list* list, double num);
void insert_main_list (Doubly_linked_list* list, double value);
void read_main_list (Doubly_linked_list* list);
void read_secondary_list (Singly_linked_list* list);

void merge_sort (Doubly_linked_node* head);
void partition (Doubly_linked_node* current, Doubly_linked_node* front, Doubly_linked_node* back);
Doubly_linked_node* merge_lists (Doubly_linked_node* a, Doubly_linked_node* b);

int main() {
    FILE* file = fopen("L1Q3.in", "r");
    if (file == NULL) {
        printf("file failed to open!");
        return 1;
    }

    char buffer[1000];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        Doubly_linked_list* main_list = (Doubly_linked_list*) malloc(sizeof(Doubly_linked_list));
        init_doubly_linked_list (main_list);
        int i = 0;
        while (buffer[i] != 'I') {
            
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
                insert_main_list (main_list, atof(temp));
            }
            else i++;
        }
    //merge_sort (main_list->head);
    read_main_list (main_list);
    free(main_list);
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

void create_doubly_linked_Node (Doubly_linked_list* list, int value) {
    Doubly_linked_node* new_node = (Doubly_linked_node*) malloc(sizeof(Doubly_linked_node));
    new_node->secondary_list = (Singly_linked_list*) malloc(sizeof(Singly_linked_list));
    new_node->num = value;
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

void create_singly_circular_linked_Node (Singly_linked_list* list, double value) {
    Singly_linked_node* new_node = (Singly_linked_node*) malloc(sizeof(Singly_linked_node));
    new_node->num = value;

    if (list->head == NULL) {
        list->tail = list->head = new_node;
        //list->tail = new_node;
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
            create_singly_circular_linked_Node (current->secondary_list, value);
        }
        current = current->next;
    }
    free(current);
}

void read_main_list (Doubly_linked_list* list) {
    Doubly_linked_node* current = (Doubly_linked_node*) malloc(sizeof(Doubly_linked_node));
    current = list->head;

    printf("[");
    while (current != NULL) {
        printf("%d", current->num);
        printf("(");
        if (current->secondary_list->head != NULL) {
            read_secondary_list (current->secondary_list);
        }
        printf(")");
        if (current->next != NULL) {printf("->");}
        current = current->next;
    }
    printf("]");
    printf("\n");
    free(current);
}

void read_secondary_list (Singly_linked_list* list) {
    Singly_linked_node* current = (Singly_linked_node*) malloc(sizeof(Singly_linked_node));
    current = list->head;

    bool control = true;
    while (control) {
        printf("%.2lf", current->num);
        if (current != list->tail) {printf("->");}
        if (current == list->tail) {control = false;}
        current = current->next;
    }
    free(current);
}

// mergesort

void partition (Doubly_linked_node* current, Doubly_linked_node* front, Doubly_linked_node* back) {
    
    Doubly_linked_node* slow;
    Doubly_linked_node* fast;

    if (current == NULL || current->next == NULL) {
        front = current;
        back = NULL;
    }
    else {
        slow = current;
        fast = current->next;
        while ( fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        front = current;
        back= slow->next;
        slow->next = NULL;
    }
}

Doubly_linked_node* merge_lists (Doubly_linked_node* a, Doubly_linked_node* b) {
    Doubly_linked_node* merged_list = NULL;

    if (a == NULL) {return b;}
    else if (b == NULL) {return a;}

    if (a->num <= b->num) {
        merged_list = a;
        merged_list->next = merge_lists (a->next, b);
    }
    else {
        merged_list = b;
        merged_list->next = merge_lists (a, b->next);
    }
    return merged_list;
}

void merge_sort (Doubly_linked_node* head) {

    Doubly_linked_node* current = head;
    Doubly_linked_node* a = NULL;
    Doubly_linked_node* b = NULL;

    if (current == NULL || current->next == NULL) {return;}

    partition (current, a, b);

    merge_sort (a);
    merge_sort (b);

    head = merge_lists (a, b);
}