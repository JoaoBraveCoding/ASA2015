#ifndef _HEADERS_H__
#define _HEADERS_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct{
  int valor;
  struct node_struct *next;
}node;

typedef struct vertex_struct{
  int id;
  int color; /*0 -unvisited/ 1 -visited but not totaly/ 2 -visited completely*/
  node* conections;
  node* endConections;
  int distance;
}vertex;

#endif
