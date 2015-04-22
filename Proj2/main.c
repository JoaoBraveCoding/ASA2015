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
  int i;
  i = *(head);
  if(*(head) < N){
    i++;
    *(head) = i;
  }
  else
    *(head)=0;
}

void identifyNegCycle(vertex* vertexs, int *queueA, int* headOfA, int* tailOfA, int nbVertex){
  node* auxPointer;
  while(!qempty(headOfA, tailOfA)){
    vertexs[queueA[*(headOfA)] - 1].controlFlag = 1;
    if(vertexs[queueA[*(headOfA)] - 1].conections!=NULL){
      auxPointer = vertexs[queueA[*(headOfA)] - 1].conections;
      while(auxPointer != NULL){
	if (vertexs[(auxPointer->vertexNb) - 1].controlFlag == 0)
	  enqueue(queueA, vertexs[(auxPointer->vertexNb) - 1].id, tailOfA, nbVertex);
	auxPointer= auxPointer->next;
      }
    }
    nextQueue(headOfA, nbVertex);
  }
  free(queueA);
}

void relax(vertex* u, vertex* v ,int  w, int* changeFlag, int* queueB, int* tailOfB, int nbVertex){
  if(v -> vertexWeight > u -> vertexWeight + w){
    v -> vertexWeight = u -> vertexWeight + w;
    v -> predecessor = u -> id;
    enqueue(queueB, v->id, tailOfB, nbVertex);
    v -> controlFlag = 0;
    *(changeFlag) = 1;
  }
}


void bellmanFord (vertex* vertexs, int nbVertex, int* queueA, int* headOfA, int*tailOfA){
  int changeFlag, headOfB, tailOfB, *queueB, i;
  node* auxPointer;
  changeFlag = headOfB = tailOfB = 0;
  queueB = (int*) malloc(nbVertex * sizeof(int));
  for (i = 0; i < nbVertex; i++){
    while (!qempty(headOfA, tailOfA)){
      if(vertexs[queueA[*(headOfA)] - 1].vertexWeight < INT_MAX/2){
	auxPointer = vertexs[queueA[*(headOfA)] - 1].conections;
	while(auxPointer != NULL){
	  relax(&(vertexs[queueA[*(headOfA)] - 1]), &(vertexs[(auxPointer->vertexNb) - 1]), auxPointer->cost, &(changeFlag), queueB, &(tailOfB), nbVertex); 
	  auxPointer = auxPointer->next;
	}
      }
      nextQueue(headOfA, nbVertex);
    }
    free (queueA);
    queueA = queueB;
    queueB = (int*) malloc(nbVertex * sizeof(int));
    *(headOfA)= 0;
    *(tailOfA) = tailOfB;
    tailOfB = headOfB = 0;
    if(changeFlag == 0){        /*condicao de paragem caso ja todos os vertices tenham o seu pesso correcto*/
      break;
    }
  }
  free(queueB);
  identifyNegCycle(vertexs, queueA, headOfA, tailOfA, nbVertex);
   
}

int main(){

  int nbVertex, nbEdges, source, beggining, end, cost, i, headOfA, tailOfA, *queueA;
  vertex *vertexs;
  node *connectionToAdd, *auxPointer, *auxPointer2;
  nbVertex = nbEdges = source = beggining = end = cost = i = tailOfA = headOfA = 0;
  vertexs = NULL;
  queueA = NULL;
  connectionToAdd = NULL;


  if(scanf("%d %d %d", &nbVertex, &nbEdges, &source) == 3){

    vertexs = (vertex*) malloc(sizeof(vertex)*nbVertex);
    queueA = (int*) malloc(nbVertex* sizeof(int));

    /*inicializar o vector de vertices e colocamos cada vertice numa queue*/
    for(i = 0; i < nbVertex; i++){
      initVertex( &(vertexs[i]) );
      vertexs[i].id = i + 1;
      enqueue( queueA, i + 1, &tailOfA, nbVertex);
    }

    vertexs[source - 1].vertexWeight = 0;
    vertexs[source - 1].controlFlag = 0;
    
    /*ciclo para leitura do input*/
    while ( scanf( "%d %d %d ", &beggining, &end, &cost) != EOF){
      connectionToAdd = (node*) malloc (sizeof(node));
      fillNode(connectionToAdd, end, cost);

      if(vertexs[beggining - 1].conections != NULL){
	connectionToAdd->next = vertexs[beggining - 1].conections;
	vertexs[beggining - 1].conections = connectionToAdd;
      }

      if(vertexs[beggining - 1].conections == NULL){
	vertexs[beggining - 1].conections = connectionToAdd;
      }
    }
    bellmanFord ( vertexs, nbVertex, queueA, &headOfA, &tailOfA);
   
    /*ciclo para imprimir o output e para fazer free as estruturas alocadas*/
    for(i = 0; i < nbVertex; i++){
      if(vertexs[i].controlFlag == 0){
	printf("%d\n",vertexs[i].vertexWeight);
      }
      if(vertexs[i].controlFlag == 1){
	printf("I\n");
      }
      if(vertexs[i].controlFlag == 2){
	printf("U\n");
      }
      auxPointer = vertexs[i].conections;
      while(auxPointer != NULL){
	auxPointer2 = auxPointer->next;
	free(auxPointer);
	auxPointer = auxPointer2;
      }
    }
    free(vertexs);
  }
  return 0;
}
