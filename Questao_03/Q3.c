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

void merge_sort (Doubly_linked_list* list);
void merge_sort_main (Doubly_linked_node** head);
void partition_main (Doubly_linked_node* current, Doubly_linked_node** front, Doubly_linked_node** back);
Doubly_linked_node* merge_lists_main (Doubly_linked_node* a, Doubly_linked_node* b);

void merge_sort_secondary (Singly_linked_node** head);
void partition_secondary (Singly_linked_node* current, Singly_linked_node** front, Singly_linked_node** back);
Singly_linked_node* merge_lists_secondary (Singly_linked_node* a, Singly_linked_node* b);

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
            
            if (buffer[i] >= '0' && buffer[i] <= '9' || buffer[i] == '-') {
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

            if (buffer[i] >= '0' && buffer[i] <= '9' || buffer[i] == '-') {
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
    merge_sort (main_list);
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
        if (value >= 0) {
            if (value > current->num && value < current->num + 1) {
            create_singly_circular_linked_Node (current->secondary_list, value);
            }
        }
        else {
            if (value < current->num && value > current->num - 1) {
            create_singly_circular_linked_Node (current->secondary_list, value);
            }
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

// mergesort_GERAL  gcc Q3.c -o Q3.exe

void merge_sort (Doubly_linked_list* list) {

    Doubly_linked_node* current = (Doubly_linked_node*) malloc(sizeof(Doubly_linked_node));
    current = list->head;

    /* while(current != NULL) {
        merge_sort_secondary (&current->secondary_list->head);
        current = current->next;
    } */
    merge_sort_main (&list->head);
    free(current);
}

// mergesort_main_list

void merge_sort_main (Doubly_linked_node** head) {

    Doubly_linked_node* current = *head;
    Doubly_linked_node* a = NULL;
    Doubly_linked_node* b = NULL;

    if (!current || !current->next) {return;}

    partition_main (current, &a, &b);

    merge_sort_main (&a);
    merge_sort_main (&b);

    *head = merge_lists_main (a, b);
}

void partition_main (Doubly_linked_node* current,
                Doubly_linked_node** front, Doubly_linked_node** back) {
    
    Doubly_linked_node* slow;
    Doubly_linked_node* fast;

    slow = current;
    fast = current;
    while (fast->next && fast->next->next) {
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
    }
    *front = current;
    *back= slow->next;
    slow->next = NULL;
}

Doubly_linked_node* merge_lists_main (Doubly_linked_node* a, Doubly_linked_node* b) {
    Doubly_linked_node* result = NULL;

    if (a == NULL) {return b;}
    else if (b == NULL) {return a;}

    if (a->num <= b->num) {
        result = a;
        result->next = merge_lists_main (a->next, b);
        result->next->prev = result;
        result->prev = NULL;
    }
    else {
        result = b;
        result->next = merge_lists_main (a, b->next);
        result->next->prev = result;
        result->prev = NULL;
    }
    return (result);
}

// mergesort_secondary_list

void merge_sort_secondary (Singly_linked_node** head) {

    Singly_linked_node* current = *head;
    Singly_linked_node* a = NULL;
    Singly_linked_node* b = NULL;

    if (current == NULL || current->next == NULL) {return;}

    partition_secondary (current, &a, &b);

    merge_sort_secondary (&a);
    merge_sort_secondary (&b);

    *head = merge_lists_secondary (a, b);
}

void partition_secondary (Singly_linked_node* current,
                Singly_linked_node** front, Singly_linked_node** back) {
    
    Singly_linked_node* slow;
    Singly_linked_node* fast;

    slow = current;
    fast = current->next;
    while ( fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = current;
    *back= slow->next;
    slow->next = NULL;
}

Singly_linked_node* merge_lists_secondary (Singly_linked_node* a, Singly_linked_node* b) {
    Singly_linked_node* result = NULL;

    if (a == NULL) {return b;}
    else if (b == NULL) {return a;}

    if (a->num <= b->num) {
        result = a;
        result->next = merge_lists_secondary (a->next, b);
    }
    else {
        result = b;
        result->next = merge_lists_secondary (a, b->next);
    }
    return (result);
}