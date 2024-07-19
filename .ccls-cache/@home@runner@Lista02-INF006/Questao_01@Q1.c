#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define linhas 1
#define size 1000
#define size_of_integers 100

typedef struct {
  int Integer[size_of_integers];
  int sizeOfIntegers;
  int sumOfIntegers;
} start;

void insertion_sort_integers (start array[], int length);
void insertion_sort_start (start array[], int length);
start simple_pass (start array_B);

int main() {

  FILE *file;
  file = fopen("L1Q1.in", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.in!\n");
    return 1;
  }
  FILE *saida;
  saida = fopen("L1Q1.out", "w+");
  if (saida == NULL) {
    printf("Erro ao abrir o arquivo.out!\n");
    return 1;
  }

  char buffer[size];
  int linhasLidas = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL/* linhasLidas < linhas */) {
    //fgets(buffer, sizeof(buffer), file);
    //printf("\n");
    //printf("linha %d\n", linhasLidas+1);
    //printf("\n");

    //printf("%s", buffer);
    start array[size];
    int sizeOfStart = 0;
    int jCont = 0;

    for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
      int iCont = 0;
      if (buffer[i] >= '0' && buffer[i] <= '9' || buffer[i] == '-') {
        array[jCont].sumOfIntegers = 0;

        while (buffer[i] != 's' && buffer[i] != '\0' && buffer[i] != '\n') {
          char num[100];
          for (int j = 0; buffer[i] != ' ' && buffer[i] != '\0' && buffer[i] != '\n'; j++, i++) {
            num[j] = buffer[i];
            num[j + 1] = '\0';
          }
          array[jCont].Integer[iCont] = atoi(num);
          array[jCont].sumOfIntegers += array[jCont].Integer[iCont];
          iCont++;
          array[jCont].sizeOfIntegers = iCont;
          i++;
        }
        jCont++;
        sizeOfStart = jCont;
      }
      if (buffer[i] == '\0') break;
    }
    insertion_sort_integers (array, sizeOfStart);
    insertion_sort_start (array, sizeOfStart);

    for (int i = 0; i < sizeOfStart; i++) {
      if (i > 0) fprintf(saida, " ");
      fprintf(saida, "start");
      //printf("start ");
      for (int j = 0; j < array[i].sizeOfIntegers; j++) {
        //printf(" %d", array[i].Integer[j]);
        fprintf(saida," %d", array[i].Integer[j]);
      }
      //printf("\n");
      //printf("soma %d\n",  array[i].sumOfIntegers);
      //printf("\n");
    }
    //printf("\n");
    fprintf(saida, "\n");
    linhasLidas++;
  }
  
  fclose(file);
  fclose(saida);
  return 0;
}

void insertion_sort_integers (start array[], int length) {

  for (int j = 0; j < length; j++) {
    for (int i = 1; i < array[j].sizeOfIntegers; i++) {
      int key = array[j].Integer[i];
      int k = i - 1;
      while (k >= 0 && array[j].Integer[k] > key) {
        array[j].Integer[k + 1] = array[j].Integer[k];
        k--;
      }
      array[j].Integer[k + 1] = key;
    }
  }
}

void insertion_sort_start (start array[], int length) {

  
  for (int i = 1; i < length; i++) {
    start key;
    key = simple_pass (array[i]);
    int k = i - 1;
    while (k >= 0 && array[k].sumOfIntegers > key.sumOfIntegers) {
      array[k + 1] = simple_pass (array[k]);
      k--;
    }
    array[k + 1] = simple_pass (key);
  }
}

start simple_pass (start array_B) {
  start array_A;
  for (int i = 0; i < array_B.sizeOfIntegers; i++) {
    array_A.Integer[i] = array_B.Integer[i];
  }
  array_A.sizeOfIntegers = array_B.sizeOfIntegers;
  array_A.sumOfIntegers = array_B.sumOfIntegers;
  return array_A;
}
