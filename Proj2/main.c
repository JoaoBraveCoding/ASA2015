#include "headers.h"

void initVertex( vertex* ver){
  ver->id = 0;
  ver-> addedToQueue = 1;
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

int qempty(limites* l){
  return l->head == l->tail;
}

void enqueue(int *q, int x, limites* l){
  q[l->tail] = x;
  (l -> tail)++;
}

void nextQueue(limites* l){
  l->head ++;
}

void identifyNegCycle(vertex* vertexs, int *queueA, limites* limOfA, int nbVertex){
  node* auxPointer;

  while(!qempty(limOfA)){
    vertexs[queueA[limOfA -> head] - 1].controlFlag = 1;
    auxPointer = vertexs[queueA[limOfA->head] - 1].conections;
    while(auxPointer != NULL){
      if (vertexs[(auxPointer->vertexNb) - 1].controlFlag == 0 && vertexs[(auxPointer->vertexNb) - 1].addedToQueue){
	vertexs[(auxPointer->vertexNb) - 1].addedToQueue = 0;
	enqueue(queueA, auxPointer->vertexNb, limOfA);
      }
      auxPointer= auxPointer->next;
    }
    nextQueue(limOfA);
  }
}

int relax(vertex* u, vertex* v ,int  w, int changeFlag, int* queueB, limites* limOfB){
  if(v->vertexWeight > u->vertexWeight + w){
    v->vertexWeight = u->vertexWeight + w;
    v->predecessor = u->id;
    enqueue(queueB, v->id, limOfB);
    v->controlFlag = 0;
    return 1;
  }
  else{
    if(changeFlag == 1){
      return 1;
    }
    else{
      return 0;
    }
  }
}


void bellmanFord (vertex* vertexs, int nbVertex, int* queueA, limites* limOfA){
  int changeFlag, *queueB, i;
  limites *limOfB;
  node* auxPointer;
  changeFlag = 0;
  limOfB = (limites*) malloc (sizeof(limites));
  limOfB->head = 0;
  limOfB->tail = 0;
  queueB = (int*) calloc(nbVertex+1, sizeof(int));
  for (i = 0; i < nbVertex; i++){
    while (!qempty(limOfA)){
      if(vertexs[queueA[limOfA -> head] - 1].vertexWeight < INT_MAX/2){
	auxPointer = vertexs[queueA[limOfA -> head] - 1].conections;
	while(auxPointer != NULL){
	  changeFlag = relax(&(vertexs[queueA[limOfA -> head] - 1]), &(vertexs[(auxPointer->vertexNb) - 1]), auxPointer->cost, changeFlag, queueB, limOfB); 
	  auxPointer = auxPointer->next;
	}
      }
      nextQueue(limOfA);
    }
    free (queueA);
    queueA = NULL;
    queueA = queueB;
    queueB = NULL;
    queueB = (int*) calloc(nbVertex+1, sizeof(int));
    limOfA -> head = 0;
    limOfA -> tail = limOfB -> tail;
    limOfB -> tail = 0;
    limOfB -> head = 0;
 if(changeFlag == 0){        /*condicao de paragem caso ja todos os vertices tenham o seu pesso correcto*/
      break;
    }
  }
  free(queueB);
  identifyNegCycle(vertexs, queueA, limOfA, nbVertex);
   
}

int main(){

  int nbVertex, nbEdges, source, beggining, end, cost, i, *queueA;
  vertex *vertexs;
  limites *limOfA;
  node *connectionToAdd;
  nbVertex = nbEdges = source = beggining = end = cost = i = 0;
  vertexs = NULL;
  queueA = NULL;
  connectionToAdd = NULL;
  limOfA =(limites*) malloc(sizeof(limites));
  limOfA -> head = 0;
  limOfA -> tail = 0;

  if(scanf("%d %d %d", &nbVertex, &nbEdges, &source) == 3){

    vertexs = (vertex*) malloc(sizeof(vertex)*nbVertex);
    queueA = (int*) calloc(nbVertex+1, sizeof(int));

    /*inicializar o vector de vertices e colocamos cada vertice numa queue*/
    for(i = 0; i < nbVertex; i++){
      initVertex( &(vertexs[i]) );
      vertexs[i].id = i + 1;
      enqueue( queueA, i + 1, limOfA);
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
    bellmanFord (vertexs, nbVertex, queueA, limOfA);
   
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
    }
    free(vertexs);
  }
  return 0;
}
