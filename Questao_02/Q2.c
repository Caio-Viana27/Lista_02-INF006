#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE_OF_BUFFER 1000
#define SIZE_OF_STACK 100
#define STRING_TEMP 21

// Bom dia meus lindos!!
// A ideia para resolver essa questão é bem simples
// basicamente eu criei duas stacks, uma principal e outra Auxiliar, onde baseado na comparação dos elementos
// feita pela função strcmp eu vou remover 'pop' ou adicionar 'push' os nomes
// dessa forma eu tenho duas stacks, que sempre que o meu próximo push na stack principal for
// de tamanho lexíco menor que o elemento do top dela, remove-se os elementos que forem necessarios
// e armazena eles na stack Auxiliar, entao faaz o 'push' do elemnto, dps retorna os para a stack principal

// EXEMPLO:   Main_Stack                  Aux_Stack

// push "B"  |    E    |  <-- 3X-pop      |        |
//           |    D    |                  |   C    |
//           |    C    |      3xpush -->  |   D    |
//           |    A    |                  |   E    |

//           |         |                  |        |
//           |         |                  |   C    |
// push "B"  |    B    |                  |   D    |
//           |    A    |                  |   E    |

//           |         |  <-- 3xpush      |        |
//           |         |                  |   C    |
//           |    B    |      3X-pop -->  |   D    |
//           |    A    |                  |   E    |

// Resultado final

//           |    E    |                  |        |
//           |    D    |                  |        |
//           |    C    |                  |        |
//           |    B    |                  |        |
//           |    A    |                  |        |

typedef struct {
    int top;
    char *stackOfStrings[20];
} Stack;

void init_Stack (Stack *stack);
void get_Name (char buffer[], Stack *Main_Stack, Stack *Aux_Stack, bool newLine);
bool Stack_is_Empty (Stack *stack);
void Push (Stack *stack, char name[]);
int Pop (Stack *stack);

FILE *file;
FILE *output;

int main () {

    file = fopen("L1Q2.in", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.in!\n");
        return 1;
    }
    output = fopen("L1Q2.out", "w+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.out!\n");
        return 1;
    }

    char buffer[SIZE_OF_BUFFER];
    while (fgets(buffer , sizeof(buffer), file) != NULL) {
        Stack Aux_Stack, Main_Stack;
        init_Stack (&Aux_Stack);
        init_Stack (&Main_Stack);

        bool newLine = true; // controla os espaços em novas linhas do arquivo.out

        get_Name (buffer, &Main_Stack, &Aux_Stack, newLine);

        fprintf(output, "\n");
    }
    fclose(file);
    fclose(output);
}

// inicia as stacks
void init_Stack (Stack *stack) {
    stack->top = -1;
    for (int i = 0; i < 20; i++) {
        stack->stackOfStrings[i] = malloc(sizeof(char) * SIZE_OF_STACK);
    }
}

// Função principal que separa os nomes e coloca nas stacks
void get_Name (char buffer[], Stack *Main_Stack, Stack *Aux_Stack, bool newLine) {

    int i = 0;
    //bool newLine = true; // controla os espaços em novas linhas do arquivo.out

    while (buffer[i] != '\0' && buffer[i] != '\n') {
        int j = 0;
        char name[STRING_TEMP];
        while (buffer[i] != ' ' && buffer[i] != '\0' && buffer[i] != '\n') {
            name[j] = buffer[i];
            name[j + 1] = '\0';
            j++;
            i++;
        }

        // Faz a checagem da ordem alfabética
        // Os dois while's do else estao tirando de uma stack e jogando pra outra
        // conforme é necessário
        if (Stack_is_Empty (Main_Stack)) {
            Push (Main_Stack, name);
            if (newLine) {
                fprintf(output, "push-%s", name);
                newLine = false;
            }
            else fprintf(output, " push-%s", name);
        }
        else if (strcmp (name, Main_Stack->stackOfStrings[Main_Stack->top]) >= 0) {
            Push (Main_Stack, name);
            fprintf(output, " push-%s", name);
        }
        else {
            int Qtd_POP = 0;
            while (Main_Stack->top > -1 && strcmp (name, Main_Stack->stackOfStrings[Main_Stack->top]) < 0) {
                char TempString[STRING_TEMP];
                int position = Pop (Main_Stack);
                 Qtd_POP++;
                strcpy (TempString, Main_Stack->stackOfStrings[position]);
                Push (Aux_Stack, TempString);
            }
            fprintf(output, " %dx-pop", Qtd_POP);
            Push (Main_Stack, name);
            fprintf(output, " push-%s", name);
            while (!Stack_is_Empty (Aux_Stack)) {
                char TempString[STRING_TEMP];
                int position = Pop (Aux_Stack);
                strcpy (TempString, Aux_Stack->stackOfStrings[position]);
                Push (Main_Stack, TempString);
                fprintf(output, " push-%s", TempString);
            }
        }
        if (buffer[i] == '\0' || buffer[i] == '\n') break;
        else i++;
    }
}

// Aqui estão as funções da stack
bool Stack_is_Empty (Stack *stack) {
    if (stack->top == -1) return true;
    else return false;
}

void Push (Stack *stack, char name[]) {
    stack->top++;
    strcpy (stack->stackOfStrings[stack->top], name);
}

int Pop (Stack *stack) {
    if (Stack_is_Empty (stack)) {
        printf("stack is already empty!");
        return -1;
    }
    else {
        int temp = stack->top;
        stack->top--;
        return temp;
    }
}

// for (int i = Main_Stack.top; i > -1; i--) {
//         printf ("%s\n", Main_Stack.stackOfStrings[i]);
//     }
//     printf("\n");