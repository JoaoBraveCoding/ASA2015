#include "headers.h"

void initVertex( vertex* ver){
  ver->id = 0;
  ver->controlFlag = 2;
  ver->conections = NULL;
  ver->vertexWeight = INT_MAX/2;
  ver->predecessor = -1;
}

void fillNode( node* n, int vertexNb, int cost){
  n-> vertexNb = vertexNb;
  n-> cost = cost;
  n-> next = NULL;
}

void realax(vertex* u, vertex* v ,int  w, int* changeFlag ){
  if(v -> vertexWeight > u -> vertexWeight + w){
    v -> vertexWeight = u -> vertexWeight + w;
    v -> predecessor = u -> id;
    changeFlag = 1;
  }
}

void bellmanFord (vertex* vertexs, int source){
  

}

int main(){

  int nbVertex, nbEdges, source, beggining, end, cost, i, changeFlag;
  vertex *vertexs;
  node *connectionToAdd;
  nbVertex = nbEdges = source = beggining = end = cost = i = changeFlag = 0;
  vertexs = NULL;


  if(scanf("%d %d %d", &nbVertex, &nbEdges, &source) == 3){

    vertexs = (vertex*) malloc(sizeof(vertex)*nbVertex);
    printf("%d %d %d\n", nbVertex,nbEdges, source);

    for(i = 0; i<nbVertex; i++){
      initVertex(&(vertexs[i]));
      vertexs[i].id = i+1;
    }

    vertex[source-1].vertexWeight = 0;

    while ( scanf( "%d %d %d ", &beggining, &end, &cost) != EOF){
      connectionToAdd = (node*) malloc (sizeof(node));
      fillNode(connectionToAdd, end, cost);

      if(beggining == end){
	printf("porcaria -> beggining = end\n");
	return 0;
      }

      if(vertexs[beggining-1].conections == NULL){
	vertexs[beggining-1].conections = connectionToAdd;
      }
      
      if(vertexs[beggining-1].conections != NULL){
	connectionToAdd->next = vertexs[beggining-1].conections;
	vertexs[beggining-1].conections = connectionToAdd;
      }
    }
    
    


    }
  return 0;
}
