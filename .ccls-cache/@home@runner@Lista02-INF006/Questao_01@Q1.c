#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define linhas 1
#define size 1000

typedef struct {
  int Integer[size];
  int sizeOfIntegers;
  int sumOfIntegers;
} start;

void insertion_sort_Integers (start array[], int length);
void insertion_sort_Start (start array[], int length);
void simple_Pass (start array_A, start array_B);
void swapping_Start (start array[], int size_A, int size_B);

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
  int linhasLidas = 1;
  int sizeOfStart = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL/* linhasLidas < linhas */) {
    
    /* printf("\n");
    printf("linha %d\n", linhasLidas);
    printf("\n"); */

    //printf("%s", buffer);
    int jCont = 0;
    array[jCont].sumOfIntegers = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
      int iCont = 0;
      if (buffer[i] >= '0' && buffer[i] <= '9') {

        while (buffer[i] != 's' && buffer[i] != '\0') {
          char num[100];
          for (int j = 0; buffer[i] != ' ' && buffer[i] != '\0'; j++, i++) {
            num[j] = buffer[i];
            num[j + 1] = '\0';
          }
          array[jCont].Integer[iCont] = atoi(num);
          array[jCont].sumOfIntegers += array[jCont].Integer[iCont];
          iCont++;
          array[jCont].sizeOfIntegers = iCont;
          i++;
        }
        /* for (int i = 0; i < iCont; i++) {
          printf("inteiro %d \n", array[jCont].Integer[i]);
        }
        //printf("size %d\n",  array[jCont].sizeOfIntegers);
        printf("soma %d\n",  array[jCont].sumOfIntegers); */
      }
      jCont++;
      array[jCont].sumOfIntegers = 0;
    }
    linhasLidas++;
    sizeOfStart++;
  }

  insertion_sort_Integers (array, sizeOfStart);
  insertion_sort_Start (array, sizeOfStart);

  for (int i = 0; i < sizeOfStart; i++) {
    for (int j = 0; j < array[i].sizeOfIntegers; j++) {
      printf("inteiro %d ", array[i].Integer[j]);
    }
    printf("\n");
    printf("soma %d\n",  array[i].sumOfIntegers);
    printf("\n");
  }
  
  fclose(file);
  return 0;
}

void insertion_sort_Integers (start array[], int length) {

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
    simple_Pass (key, array[i]);

    int k = i - 1;
    while (k >= 0 && array[k].sumOfIntegers > key.sumOfIntegers) {
      simple_Pass(array[k + 1], array[k]);
      k--;
    }
    simple_Pass (array[k + 1], key);
  }
}

void simple_Pass (start array_A, start array_B) {
  for (int i = 0; i < array_A.sizeOfIntegers; i++) {
    array_A.Integer[i] = array_B.Integer[i];
  }
  array_A.sizeOfIntegers = array_B.sizeOfIntegers;
  array_A.sumOfIntegers = array_B.sumOfIntegers;
}
