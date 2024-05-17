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
    int i, j, m, p;
    int vistos[10];

    //Verificamos las filas
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 10; j++)
            vistos[j] = 0;
        for (j = 0; j < 9; j++){
            int num = n->sudo[i][j];
            if (num != 0){
                if (vistos[num] == 1){
                    return 0;
                }
                vistos[num] = 1;
            }
        }
    }
    //Verificamos las columnas
    for (j = 0; j < 9; j++){
        for (i = 0; i < 10; i++)
            vistos[i] = 0;
        for (i = 0; i < 9; i++){
            int num = n->sudo[i][j];
            if (num != 0){
                if (vistos[num] == 1){
                    return 0;
                }
                vistos[num] = 1;
            }
        }
    }
    //Verificamos las submatrices
    for (m = 0; m < 9; m++){
        for (i = 0; i < 10; i++)
            vistos[i] = 0;
        for (p = 0; p < 9; p++){
            int row = 3 * (m / 3) + (p / 3);
            int col = 3 * (m % 3) + (p % 3);
            int num = n->sudo[row][col];
            if (num != 0){
                if (vistos[num] == 1){
                    return 0;
                }
                vistos[num] = 1;
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n) {
    List* list = createList();

    //Encontramos la primera casilla vacía
    int encontrado = 0;
    int row = 0, col = 0;
    for (int i = 0; i < 9 && !encontrado; i++) {
        for (int j = 0; j < 9 && !encontrado; j++) {
            if (n->sudo[i][j] == 0) {
                row = i;
                col = j;
                encontrado = 1;
            }
        }
    }

    // Generar los nodos adyacentes cambiando el valor de la primera casilla vacía de 1 a 9
    if (encontrado) {
        for (int value = 1; value <= 9; value++) {
            Node* new_node = copy(n);
            new_node->sudo[row][col] = value;
            if (is_valid(new_node)) {
                pushBack(list, new_node);
            }
            else{
                free(new_node);
            }
        }
    }

    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (n->sudo[i][j] == 0){
                return 0; //Es casilla vacía
            }
        }
    }
    return 1; //Todas las casillas están llenas
}

Node* DFS(Node* initial, int* cont){
  //Creamos una pila S con el nodo inicial
    Stack * S = createStack();
    push(S, initial);

    *cont = 0;

    //Mientras la pila no esté vacía
    while (!is_empty(S)){
        (*cont)++;
        
        //Sacamos el último nodo de la pila
        Node* current = (Node*)top(S);
        pop(S);

        //Verificar si corresponde a un estado final (solución)
        if (is_final(current)){
            clean(S);
            free(S);
            return current;
        }

        //Obtenemos la lista de nodos adyacentes
        List* adj_nodes = get_adj_nodes(current);

        //Agregamos uno por uno los nodos a la pila
        Node* adj_node = (Node*)first(adj_nodes);
        while (adj_node != NULL){
            push(S, adj_node);
            adj_node = (Node*)next(adj_nodes);
        }
        //Liberar la memoria del nodo actual
        free(current);

        //Liberar la memoria de la lista de nodos adyacentes
        clean(adj_nodes);
        free(adj_nodes);
    }
    free(S);
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