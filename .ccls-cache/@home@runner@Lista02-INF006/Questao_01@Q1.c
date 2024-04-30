#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define linhas 1
#define size 1000

typedef struct {
  int Intenger[size];
  int sumOfIntegers;
} start;

int main() {

  FILE *file;
  file = fopen("L1Q1.in", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.in!\n");
    return 1;
  }
  FILE *saida;
  saida = fopen("L1Q1.out", "w");
  if (saida == NULL) {
    printf("Erro ao abrir o arquivo.out!\n");
    return 1;
  }
  fclose(saida);

  start array[size];

  char buffer[size];
  int linhasLidas = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL/* linhasLidas < linhas */) {

    array[0].sumOfIntegers = 0;
    
    printf("\n");
    printf("linha %d\n", linhasLidas);
    printf("\n");

    //printf("%s", buffer);
    int jCont = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
      int iCont = 0;
      if (buffer[i] >= '0' && buffer[i] <= '9') {

        while (buffer[i] != 's' && buffer[i] != '\0') {
          char num[100];
          for (int j = 0; buffer[i] != ' ' && buffer[i] != '\0'; j++, i++) {
            num[j] = buffer[i];
            num[j + 1] = '\0';
          }
          array[jCont].Intenger[iCont] = atoi(num);
          array[jCont].sumOfIntegers += array[jCont].Intenger[iCont];
          iCont++;
          i++;
        }
        for (int i = 0; i < iCont; i++) {
          printf("inteiro %d \n", array[jCont].Intenger[i]);
        }
        printf("soma %d\n",  array[jCont].sumOfIntegers);
      }
      jCont++;
      array[jCont].sumOfIntegers = 0;
    }
    linhasLidas++;
  }
  fclose(file);
  return 0;
}
