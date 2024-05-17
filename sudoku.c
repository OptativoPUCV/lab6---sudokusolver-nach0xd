#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

    return 1;
}


List* get_adj_nodes(Node* n) {
    List* list = createList();

    // Encontrar la primera casilla vacía (asumimos que las casillas vacías tienen el valor 0)
    int found = 0;
    int row = 0, col = 0;
    for (int i = 0; i < 9 && !found; i++) {
        for (int j = 0; j < 9 && !found; j++) {
            if (n->sudo[i][j] == 0) {
                row = i;
                col = j;
                found = 1;
            }
        }
    }

    // Generar los nodos adyacentes cambiando el valor de la primera casilla vacía de 1 a 9
    if (found) {
        for (int value = 1; value <= 9; value++) {
            Node* new_node = copy(n);
            new_node->sudo[row][col] = value;
            pushBack(list, new_node);
        }
    }

    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/