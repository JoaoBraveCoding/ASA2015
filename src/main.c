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
      return 0;
    }
    iterator= iterator->next;
  }
  return 1;
}

int main(){

  int nbVertex, nbEdges, first, second;
  vertex erdos;
  nbVertex = nbEdges = 0;
  vertex *people;
  first = second = 0;

  initVertex( &erdos);
  if( scanf("%d %d %d", &nbVertex, &nbEdges, &erdos.id) == 3){
    printf("nbVertex: %d nbEdges: %d Erdos: %d\n", nbVertex, nbEdges, erdos.id);
    

    people = (vertex*) malloc(sizeof(vertex)*nbVertex);
    people[(erdos.id) -1] = erdos;
    

    while( scanf("%d %d", &first, &second) != EOF ){
      
      node* conection;
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
      
      if(people[first-1].conection != NULL){
	if(!(hasConection(people[first-1].conections, second))){
	  endConections->next = conection1;
	  endConections = conection1;
	}
      }
      if(people[second-1].conection != NULL){
	if(!(hasConection(people[second-1].conections, first))){
	  endConections->next = conection2;
	  endConections = conection2;
	}
      }
     
      if(people[first-1].conections == NULL){
	people[first-1].conections = conection1;
	people[first-1].endConections = conection1; 
      }
      if(people[second-1].conections == NULL){
	people[second-1].conections = conection2;
	people[second-1].endConections = conection2; 
      }
    }

    
  }  
  return 0;
}
