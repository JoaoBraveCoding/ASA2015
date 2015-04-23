#ifndef _HEADERS_H__
#define _HEADERS_H__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct node_struct{
  int vertexNb;
  int cost;
  struct node_struct *next;
}node;

typedef struct vertex_struct{
  int id;
  int controlFlag;  /*0 -value/ 1 - I/ 2 - U*/
  node* conections;
  int vertexWeight;
  int predecessor;
  int addedToQueue; /*1 not added/ 0 added*/
}vertex;

typedef struct limites_struct{
  int head;
  int tail;
}limites;

#endif
