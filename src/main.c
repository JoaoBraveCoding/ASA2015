#include "headers.h"

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


void visitor (vertex* ver, vertex* people, int* max){
  node *nodeIterator;
  nodeIterator = NULL;
  /* printf("estou no visitor crl %d ->\n", ver->id); */
  if(ver != NULL){
    nodeIterator = ver->conections;
    while(nodeIterator != NULL){
      /* printf("estou 1º while valor-> %d\n", nodeIterator->valor); */
      if(people[(nodeIterator->valor)-1].color != 1 && people[(nodeIterator->valor)-1].color != 2){
	/* printf("estou 1º while DENTRO DO IF\n"); */
	people[(nodeIterator->valor)-1].color = 1;
	people[(nodeIterator->valor)-1].distance = (ver->distance) + 1;
      }
      if(people[(nodeIterator->valor)-1].distance > (ver->distance) + 1 && people[(nodeIterator->valor)-1].color != 0){
	people[(nodeIterator->valor)-1].distance = (ver->distance) + 1;
      }
     
      nodeIterator = nodeIterator->next;
    }
    ver->color = 2;
    nodeIterator = NULL;
    nodeIterator = ver-> conections;
   
    while(nodeIterator != NULL && ver->color == 2  ){
      
      /* printf("estou 2º while %d -> valor %d -> cor\n",nodeIterator->valor, people[(nodeIterator->valor -1)].color ); */
      if(people[(nodeIterator->valor -1)].color == 1){
	visitor( &(people[(nodeIterator->valor -1)]), people, max);
      }
      nodeIterator= nodeIterator->next;
    }
  }
}

int main(){

  int i;

  int nbVertex, nbEdges, first, second;
  vertex erdos;
  vertex *people;
  int *result, max;
  node *fir, *sec;
  nbVertex = nbEdges = max = i = 0;
  first = second = 0;
  fir = sec = NULL;
  people = NULL;

  initVertex( &erdos);
  if( scanf("%d %d %d", &nbVertex, &nbEdges, &erdos.id) == 3){
    printf("nbVertex: %d nbEdges: %d Erdos: %d\n", nbVertex, nbEdges, erdos.id); 


    people = (vertex*) malloc(sizeof(vertex)*nbVertex);

    for(i = 0; i<nbVertex; i++){
      initVertex(&(people[i]));
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

    visitor(&people[erdos.id -1], people, &max);
    /* 
    for( i = 0; i<=nbVertex-1; i++){
      printf("%d : %d : %d : %d\n", people[i].id, people[i].conections->valor, people[i].distance, people[i].color);
    }
    */
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
	free(fir);
	sec = sec-> next;
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
