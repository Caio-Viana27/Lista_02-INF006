#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int top;
    char *stackOfStrings[20];
} Stack;

void init_Stack (Stack stack);
void get_Name (char buffer[], Stack Main_Stack, Stack Aux_Stack);
bool Stack_is_Empty (Stack stack);
void Push (Stack stack, char name[]);
char* Pop (Stack stack);

int main () {

    FILE *file = fopen("L1Q2.in", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.in!\n");
        return 1;
    }

    char buffer[1000];
    while (fgets(buffer , sizeof(buffer), file) != NULL) {
        Stack Aux_Stack, Main_Stack;
        init_Stack (Aux_Stack);
        init_Stack (Main_Stack);

        get_Name (buffer, Main_Stack, Aux_Stack);

        for (int i = Main_Stack.top; i > -1; i--) {
            printf ("%s\n", Main_Stack.stackOfStrings[i]);
        }
    }
    fclose(file);
}

void init_Stack (Stack stack) {
    stack.top = -1;
    for (int i = 0; i < 20; i++) {
        stack.stackOfStrings[i] = malloc(sizeof(char) * 100);
    }
}

void get_Name (char buffer[], Stack Main_Stack, Stack Aux_Stack) {

    int i = 0;
    while (buffer[i] != '\0' && buffer[i] != '\n') {
        int j = 0;
        char name[21];
        while (buffer[i] != ' ' && buffer[i] != '\0' && buffer[i] != '\n') {
            name[j] = buffer[i];
            name[j + 1] = '\0';
            j++;
            i++;
        }
        if (Stack_is_Empty (Main_Stack)) {
            Push (Main_Stack, name);
        }
        else if (strcmp (name, Main_Stack.stackOfStrings[Main_Stack.top]) >= 0) {
            Push (Main_Stack, name);
        }
        else {
            while (Main_Stack.top > -1 && strcmp (name, Main_Stack.stackOfStrings[Main_Stack.top]) < 0) {
                char string[21];
                strcpy (string, Pop (Main_Stack));
                Push (Aux_Stack, string);
            }
            Push (Main_Stack, name);
            while (!Stack_is_Empty (Aux_Stack)) {
                char string[21];
                strcpy (string, Pop (Aux_Stack));
                Push (Main_Stack, string);
            }
        }
    }
}

bool Stack_is_Empty (Stack stack) {
    if (stack.top == -1) return true;
    else return false;
}

void Push (Stack stack, char name[]) {
    stack.top++;
    strcpy (stack.stackOfStrings[stack.top], name);
}

char* Pop (Stack stack) {
    if (Stack_is_Empty) {
        printf("stack is already empty!");
        return NULL;
    }
    else {
        stack.top--;
        return stack.stackOfStrings[stack.top++];
    }
}