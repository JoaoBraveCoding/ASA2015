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
  if (*(tail) == N )      
    *(tail) = 0;
  else
    ( *(tail)) ++;
}


/* void visitor (vertex* people, node* queue, node* endQueue){ */
void visitor (vertex* people, int* queue, int* tail, int* head, int N){
  node *nodeIterator, *toAdd;
  nodeIterator = toAdd = NULL;
  
  if(!(qempty(head, tail))){
      nodeIterator = people[queue[*(head)]-1].conections;
    while(nodeIterator != NULL){

      if(people[(nodeIterator->valor)-1].color == 0){
	people[(nodeIterator->valor)-1].color = 1;
	people[(nodeIterator->valor)-1].distance = people[queue[*(head)] - 1].distance + 1;
	
	enqueue(queue, nodeIterator->valor,  tail, N);
       
      }
      nodeIterator = nodeIterator->next;
    }
    people[queue[*(head)] - 1].color = 2;
    
  }
}

int main(){

  int i;

  int head = 0;
  int tail = 0;
  int* v;

  int nbVertex, nbEdges, first, second;
  vertex erdos;
  vertex *people;
  int *result, max;
  node *fir, *sec, *queue, *endQueue;
  nbVertex = nbEdges = max = i = 0;
  first = second = 0;
  fir = sec = queue = endQueue = NULL;
  people = NULL;

  initVertex( &erdos);
  
  if( scanf("%d %d %d", &nbVertex, &nbEdges, &erdos.id) == 3){

    people = (vertex*) malloc(sizeof(vertex)*nbVertex);
    
    v = (int*) malloc(sizeof(int)* nbVertex);

    for(i = 0; i<nbVertex; i++){
      initVertex(&(people[i]));
      v[i] = 0;
    }

    people[(erdos.id) -1] = erdos;
    
    while( scanf("%d %d ", &first, &second) != EOF ){
      fir = (node*) malloc(sizeof(node));
      sec = (node*) malloc(sizeof(node));

      fir->next = NULL;
      sec->next= NULL;

      sec->valor = second;
      fir->valor = first;

      if(people[first-1].id == 0){
	people[first-1].id = first;
      }
      if(people[second-1].id == 0){
	people[second-1].id = second;
      }
      
      if(people[first-1].conections != NULL){
	if(sec->valor != erdos.id && sec->valor != people[first-1].id){ 
	  if((hasConection(people[first-1].conections, second)) == 0){
	    (people[first-1].endConections)->next = sec;
	    people[first-1].endConections = sec;
	  }
	}
      }
      if(people[second-1].conections != NULL){
	if(fir->valor != erdos.id && fir->valor != people[second-1].id){
	  if((hasConection(people[second-1].conections, first)) == 0){
	    (people[second-1].endConections)->next = fir;
	    people[second-1].endConections = fir;
	  }
	}
      }
     
      if(people[first-1].conections == NULL){
	if(sec->valor != erdos.id && sec->valor != people[first-1].id ){ 
	  people[first-1].conections = sec;
	  people[first-1].endConections = sec;
	} 
      }
      if(people[second-1].conections == NULL){
	if(fir->valor != erdos.id && fir->valor != people[second-1].id){
	  people[second-1].conections = fir;
	  people[second-1].endConections = fir; 
	}
      }
    }
    
    enqueue(v, erdos.id, &tail, nbVertex);
    while( head != tail){
      visitor(people, v, &tail, &head, nbVertex);
      
      if (head < nbVertex){
	head++;
      }
      else{
	head = 0;
      }
    }

    for( i = 0; i<nbVertex; i++){
      if(people[i].distance > max){
        max = people[i].distance;
      }
    }
    result = (int*) malloc(sizeof(int)*(max+1));
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
    for( i = 0; i<=max; i++){
      printf("%d\n", result[i]);
    }
     
    free(people);
    free(result);
  }  
  return 0;
}
