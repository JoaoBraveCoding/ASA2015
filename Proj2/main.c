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

void nextQueue(int* head, int N){
  if(*(head) < N)
    *(head)++;
  else
    *(head)=0;
}

void relax(vertex* u, vertex* v ,int  w, int* changeFlag, int* queueB, int* tailOfB, int vertexNb){
  if(v -> vertexWeight > u -> vertexWeight + w){
    v -> vertexWeight = u -> vertexWeight + w;
    v -> predecessor = u -> id;
    endQueue(queueB, v->id, tailOfB, vertexNb);
    changeFlag = 1;
  }
}

void bellmanFord (vertex* vertexs, int source, int nbVertex, int* queueA, int* queueB, int vertexNb){
  int changeFlag, headOfA, headOfB, tailOfA, tailOfB;
  changeFlag = headOfB = headOfA = tailOfB = tailOfA = 0;
  for (i = 0; i<nbVertex; i++){
    while (!qempty(&headOfA, &tailOfA)){
      
      auxPointer = vertexs[queueA[headOfA]-1].conections;
      if(vertexs[queueA[headOfA]-1].vertexWeight < INT_MAX/2){
	while(auxPointer != NULL){
	  relax(&(vertexs[head-1]), &(vertex[(auxPointer->vertexNb)-1]), auxPointer->cost, &(changeFlag), queueB, &(tailOfB), vertexNb); 
	  auxPointer = auxPointer->next;
	}
      }
      nextQueue(&(headOfA), vertexNb);
    
    }
    free (queueA);
    queueA = queueB;
    queueB = (int*) calloc(vertexNb, sizeof(int));
    headOfA= 0;
    tailOfA = tailOfB;
    tailOfB = headOfB = 0;
    if(changeFlag = 0){
      free (queueB);
      break;
    }
  }
}

int main(){

  int nbVertex, nbEdges, source, beggining, end, cost, i;
  vertex *vertexs;
  node *connectionToAdd;
  nbVertex = nbEdges = source = beggining = end = cost = i = 0;
  vertexs = NULL;


  if(scanf("%d %d %d", &nbVertex, &nbEdges, &source) == 3){

    vertexs = (vertex*) malloc(sizeof(vertex)*nbVertex);
    queueA = (int*) calloc(nbVertex, sizeof(int));
    queueB = (int*) calloc(nbVertex, sizeof(int));

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
