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

void initVertex( vertex* i){
  i->id = i->color = i->distance = 0;
  i->conections = i->endConections = NULL;
}

void initNode ( node* n, int value){
  n-> valor = value;
  n-> next = NULL;
}

int hasConection ( node* person, int conection){
  node* iterator;
  iterator = NULL;
  iterator = person;
  while(iterator != NULL){
    if (iterator->valor == conection){
      return 1;
    }
    iterator= iterator->next;
  }
  return 0;
}

int qempty(int* head, int *tail){
  return *(head) == *(tail);
}

void enqueue(int *q, int x, int* tail, int N){
  q[*(tail)] = x;
  if (*(tail) == N)      
    *(tail) = 0;
  else
    (*(tail))++;
}

void visitor (vertex* people, int* queue, int* tail, int* head, int N, int* max){
  node *nodeIterator, *toAdd;
  nodeIterator = toAdd = NULL;

  if(!(qempty(head, tail))){
      nodeIterator = people[queue[*(head)]-1].conections;

    while(nodeIterator != NULL){
      if(people[(nodeIterator->valor)-1].color == 0){
	people[(nodeIterator->valor)-1].color = 1;
	people[(nodeIterator->valor)-1].distance = people[queue[*(head)]-1].distance + 1;
	enqueue(queue, nodeIterator->valor, tail, N);
      }

      if(people[(nodeIterator->valor)-1].distance > *(max))
	*(max) = people[(nodeIterator->valor)-1].distance;

      nodeIterator = nodeIterator->next;
    }
    people[queue[*(head)]-1].color = 2;
  }
}

void addConnection( vertex* people, int person, node* toAdd, int erdos){
  if(people[person-1].id == 0)
    people[person-1].id = person;

  if(people[person-1].conections != NULL){
    if(toAdd->valor != erdos && person != toAdd->valor){ 
      if((hasConection(people[person-1].conections, toAdd->valor)) == 0){
	(people[person -1].endConections)->next = toAdd;
	people[person-1].endConections = toAdd;
      }
    }
    else
      free(toAdd);
  }

  if(people[person - 1].conections == NULL){
    if(toAdd->valor != erdos && person != toAdd->valor){ 
      people[person-1].conections = toAdd;
      people[person-1].endConections = toAdd;
    }
    else
      free(toAdd);
  }
}

int main(){

  int nbVertex, nbEdges, first, second, i, head, tail, max, erdos;
  int *result, *v;
  vertex *people;
  node *fir, *sec, *queue, *endQueue;
  nbVertex = nbEdges = max = i = head = tail = 0;
  first = second = 0;
  fir = sec = queue = endQueue = NULL;
  people = NULL;

  if( scanf("%d %d %d", &nbVertex, &nbEdges, &erdos) == 3){

    people = (vertex*) malloc(sizeof(vertex)*nbVertex);    
    v = (int*) calloc(nbVertex, sizeof(int));

    for(i = 0; i<nbVertex; i++){
      initVertex(&(people[i]));
    }

    people[erdos -1].id = erdos;
    while( scanf("%d %d ", &first, &second) != EOF ){
      fir = (node*) malloc(sizeof(node));
      sec = (node*) malloc(sizeof(node));

      initNode(fir, first);
      initNode(sec, second);
      
      addConnection(people, first, sec, erdos);
      addConnection(people, second, fir, erdos);
    }
    
    enqueue(v, erdos, &tail, nbVertex);
    while( !qempty(&head, &tail) ){
      visitor(people, v, &tail, &head, nbVertex, &max);
      if (head < nbVertex)
	head++;
      else
	head = 0;
    }

    result = (int*) calloc((max+1), sizeof(int));
    result[0] = max;

    for( i = 0; i<nbVertex; i++){
      if(people[i].distance != 0){
	result[people[i].distance] += 1;
      }
      sec = people[i].conections;
      while( sec != NULL){
	fir = sec;
	sec = sec-> next;
	free(fir);
      }
    }

    for( i = 0; i<=max; i++)
      printf("%d\n", result[i]);

    free(people);
    free(v);
    free(result);
  }  
  return 0;
}
