#ifndef ITEM_H
#define ITEM_H

typedef struct {
  int id;           
  double value;    
} Item;

#define id(A)          (A.id)                           // retorna identificador do nó
#define value(A)        (A.value)                       // retorna valor do nó
#define more(A, B)      (value(A) > value(B))           // compara nós, por valor
#define exch(A, B)      { Item t = A; A = B; B = t; }   // troca dois nós

#endif
