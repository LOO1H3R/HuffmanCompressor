#include <stdlib.h>
#include "pq.h"

struct pq_str {
	void ** heap;		/* heap es el arreglo que almacenará los datos 
                     a manera de un heap */
	int capacity;	  /* capacidad/tamaño físico del arreglo **/
	int size;				/* tamaño lógico de la cola de prioridad 
                     <--> posición del siguiente elemento a insertar */
	CompareFunc compare;	/* Función de comparación entre dos datos */
};

pq * pq_create(int initialCapacity, CompareFunc compare) {
	pq * queue = (pq * ) malloc(sizeof(struct pq_str));
	if(initialCapacity < 1) initialCapacity = 1;
	queue->capacity     = initialCapacity;
	queue->size         = 0;
	queue->compare      = compare;
	queue->heap         = (void *) malloc(initialCapacity * sizeof(void *));
	return queue;
}

int parent(int child) 
{
	//if(child == 0) return -1;
	return (child - 1) / 2;   // (0 - 1) / 2 = -1 / 2 = 0
}

void swap(void ** a, void ** b) {
	void * c = *a;
	*a = *b;
	*b =  c;
}
//6, 3, 7, 2, 5, 1, 8, 0, 4,
void pq_offer(pq * queue, void * data)
{
	queue->heap[queue->size] = data;
	int c = queue->size;
	int p = parent(c);

	while(c > 0 && queue->compare(queue->heap[c], queue->heap[p]) < 0) 
  {
		swap(&queue->heap[c], &queue->heap[p]);
		c = p;
		p = parent(p);
	}
	queue->size ++;
}

void * pq_peek(pq * queue) {
	if(queue->size == 0) return NULL;
	else return queue->heap[0];
}

int left(int parent) {
	return 2 * parent + 1;
}

int right(int parent) {
	return 2 * parent + 2;
}

void * pq_poll(pq * queue) {
	if(queue->size == 0) return NULL;
	void * toPoll = queue->heap[0];
	queue->size --;
	if(queue->size == 0) return toPoll;

	queue->heap[0] = queue->heap[queue->size];
	int parent = 0;
	int parentIsMin = 0;
	while(!parentIsMin) {
		int min = parent;
		int l = left(parent);
		int r = right(parent);
    /* encuentra el nodo mas chico entre izq y der (l / r) */
		if(l < queue->size && queue->compare(queue->heap[l], queue->heap[parent]) < 0) min = l;
		if(r < queue->size && queue->compare(queue->heap[r], queue->heap[min]) < 0) min = r;
    
		if(min != parent) {
			swap(&queue->heap[parent], &queue->heap[min]);
			parent = min;
		} else {
			parentIsMin = 1;
		}
	}
	return toPoll;
}

int pq_size(pq * queue) 
{
	return queue->size;
}
