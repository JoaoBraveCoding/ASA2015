#include "headers.h"

void initVertex( vertex* i){
  i->id = i->color = i->distance = 0;
  i->conections = i->endConections = NULL;
}

int hasConection ( node* person, int conection){
  node* iterator;
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
      if(people[(nodeIterator->valor)-1].distance > (ver->distance) + 1){
	people[(nodeIterator->valor)-1].distance = (ver->distance) + 1;
      }
      if(people[(nodeIterator->valor)-1].distance > *(max)){
	*(max) = people[(nodeIterator->valor)-1].distance;
      }
      nodeIterator = nodeIterator->next;
    }
    ver->color = 2;
    
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
  node *conection1, *conection2;
  nbVertex = nbEdges = max = 0;
  first = second = 0;

  initVertex( &erdos);
  if( scanf("%d %d %d", &nbVertex, &nbEdges, &erdos.id) == 3){
    /* printf("nbVertex: %d nbEdges: %d Erdos: %d\n", nbVertex, nbEdges, erdos.id); */
    

    people = (vertex*) malloc(sizeof(vertex)*nbVertex);
    people[(erdos.id) -1] = erdos;
    
    while( scanf("%d %d ", &first, &second) != EOF ){
      conection1 = (node*) malloc(sizeof(node));
      conection2 = (node*) malloc(sizeof(node));

      conection1->valor = second;
      conection2->valor = first;

      if(people[first-1].id == 0){
	initVertex( &(people[first-1]));
	people[first-1].id = first;
      }
      if(people[second-1].id == 0){
	initVertex( &(people[second-1]));
	people[second-1].id = second;
      }
      
      if(people[first-1].conections != NULL){
	if(conection1->valor != erdos.id){ 
	  if((hasConection(people[first-1].conections, second)) == 0){
	    (people[first-1].endConections)->next = conection1;
	    people[first-1].endConections = conection1;
	  }
	}
      }
      if(people[second-1].conections != NULL){
	if(conection2->valor != erdos.id){
	  if((hasConection(people[second-1].conections, first)) == 0){
	    (people[second-1].endConections)->next = conection2;
	    people[second-1].endConections = conection2;
	  }
	}
      }
     
      if(people[first-1].conections == NULL){
	if(conection1->valor != erdos.id){ 
	  people[first-1].conections = conection1;
	  people[first-1].endConections = conection1;
	} 
      }
      if(people[second-1].conections == NULL){
	if(conection2->valor != erdos.id){
	  people[second-1].conections = conection2;
	  people[second-1].endConections = conection2; 
	}
      }
    }

    visitor(&people[erdos.id -1], people, &max);

    /* for( i = 0; i<=nbVertex-1; i++){
      printf("%d : %d : %d : %d\n", people[i].id, people[i].conections->valor, people[i].distance, people[i].color);
    }*/
    
    result = (int*) malloc(sizeof(int)*(max+1));
    result[0] = max;
    for( i = 0; i<=nbVertex-1; i++){
      if(people[i].distance != 0){
	result[people[i].distance] += 1;
      }
      conection1 = people[i].conections;
      while( conection1 != NULL){
	conection2 = conection1;
	conection1 = conection1-> next;
	free(conection2);
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
