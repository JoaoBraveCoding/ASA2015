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
  queueB = (int*) calloc(nbVertex, sizeof(int));
  printf("antes do for\n");
  for (i = 0; i<nbVertex; i++){
    while (!qempty(headOfA, tailOfA)){
      auxPointer = vertexs[queueA[*(headOfA)]-1].conections;
      printf("depois de dar um valor ao auxpointer\n");
      if(vertexs[queueA[*(headOfA)]-1].vertexWeight < INT_MAX/2){
	printf(" entrei no if do INT_Max %d\n", vertexs[queueA[*(headOfA)]-1].id);
	while(auxPointer != NULL){
	  printf("entrei no while do auxpointer != NULL adj = %d\n", auxPointer->vertexNb);
	  relax(&(vertexs[queueA[*(headOfA)]-1]), &(vertexs[(auxPointer->vertexNb)-1]), auxPointer->cost, &(changeFlag), queueB, &(tailOfB), nbVertex); 
	  auxPointer = auxPointer->next;
	  printf("atribuicao do pointer = next\n");
	}
	printf("sai do while\n");
      }
      nextQueue(headOfA, nbVertex);
      printf("preso no while\n");
    }
    printf("antes de sair no for\n");
    free (queueA);
    queueA = queueB;
    queueB = (int*) calloc(nbVertex, sizeof(int));
    *(headOfA)= 0;
    *(tailOfA) = tailOfB;
    tailOfB = headOfB = 0;
    if(changeFlag == 0){
      free (queueB);
      break;
    }
  }
   while(!qempty(headOfA, tailOfA)){
     vertexs[queueA[*(headOfA)]-1].controlFlag = 1;
     nextQueue(headOfA, nbVertex);
    }
}

int main(){

  int nbVertex, nbEdges, source, beggining, end, cost, i, headOfA, tailOfA, *queueA;
  vertex *vertexs;
  node *connectionToAdd;
  nbVertex = nbEdges = source = beggining = end = cost = i = tailOfA = headOfA = 0;
  vertexs = NULL;


  if(scanf("%d %d %d", &nbVertex, &nbEdges, &source) == 3){

    vertexs = (vertex*) malloc(sizeof(vertex)*nbVertex);
    queueA = (int*) calloc(nbVertex, sizeof(int));


    for(i = 0; i<nbVertex; i++){
      initVertex(&(vertexs[i]));
      vertexs[i].id = i+1;
      enqueue( queueA, i+1, &tailOfA, nbVertex);
    }
    printf("cenas criadas\n");
    vertexs[source-1].vertexWeight = 0;
    vertexs[source-1].controlFlag = 0;

    while ( scanf( "%d %d %d ", &beggining, &end, &cost) != EOF){
      connectionToAdd = (node*) malloc (sizeof(node));
      fillNode(connectionToAdd, end, cost);

      if(beggining == end){
	printf("porcaria -> beggining = end\n");
	return 0;
      }

      if(vertexs[beggining-1].conections != NULL){
	connectionToAdd->next = vertexs[beggining-1].conections;
	vertexs[beggining-1].conections = connectionToAdd;
      }

      if(vertexs[beggining-1].conections == NULL){
	vertexs[beggining-1].conections = connectionToAdd;
      }
    }
    printf("antes do bell\n");
    bellmanFord ( vertexs, nbVertex, queueA, &headOfA, &tailOfA);
   
    for(i = 0; i<nbVertex; i++){
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
    

  }
  return 0;
}
