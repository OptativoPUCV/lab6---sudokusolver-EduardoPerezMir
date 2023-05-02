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
    int validador[10] = {};
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (n->sudo[i][j] != 0)
            {
                if (validador[n->sudo[i][j]] == 1)
                    return 0;
                else
                    validador[n->sudo[i][j]] = 1;
            }
        }
        for (int w = 0; w < 10; w++)
            validador[w] = 0;
        
        for (int j = 0; j < 9; j++)
        {
            if (n->sudo[j][i] != 0)
            {
                if (validador[n->sudo[j][i]] == 1)
                    return 0;
                else
                    validador[n->sudo[j][i]] = 1;
            }
        }
        for (int w = 0; w < 10; w++)
            validador[w] = 0;
        for (int indice = 0; indice < 9; indice++)
        {
            int j = 3 * (i / 3) + (indice / 3);
            int k = 3 * (i % 3) + (indice % 3);
            
            if (n->sudo[j][k] != 0)
            {
                if (validador[n->sudo[j][k]] == 1)
                    return 0;
                else
                    validador[n->sudo[j][k]] = 1;
            }
        }
        for (int w = 0; w < 10; w++)
            validador[w] = 0;
    }
    
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list = createList();
    int posiblesDigitos = 1;
    Node* nAux;
    int indicador;
    
    for (int k = 0; k < 9; k++)
    {
        indicador = 0;
        nAux = copy(n);
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (nAux->sudo[i][j] == 0)
                {
                    nAux->sudo[i][j] = posiblesDigitos;
                    posiblesDigitos++;
                    indicador = 1;
                    break;
                }
            }
            if (indicador == 1)
                break;
        }
        if (indicador && is_valid(nAux))
            pushBack(list, nAux);
    }
    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (n->sudo[i][j] == 0)    return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* pila = createStack();
    Node* nAux = createNode();
    List* listaAux = createList();
    *cont = 0;
    
    push(pila, initial);
    while (is_empty(pila))
    {
        nAux = first(pila);
        pop(pila);
        
        if (is_final(nAux))
        {
            return nAux;
        }
        else
        {
            listaAux = get_adj_nodes(nAux);
            while (is_empty(listaAux))
            {
                push(pila, first(listaAux));
                popFront(listaAux);
            }
        }
        (*cont)++;
    }
    
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