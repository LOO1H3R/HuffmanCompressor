#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

typedef struct pq_str pq;
typedef int (*CompareFunc) (void *, void *);

/* crea una priority queue de capacidad "initialCapacity" y utiliza
"CompareFunc" para ordenar los elementos. */
pq * pq_create(int initialCapacity, CompareFunc);

/* inserta en la cola de prioridad */
void pq_offer(pq * , void *);

/* dime que elemento sigue en la cola de prioridad (NO REMUEVE) */
void * pq_peek (pq *);

/* remueve un elemento de la cola de priodad */
void * pq_poll (pq *);

/* devuelve el numero de elementos actual en la cola de prioridad
TIP: Es el indice donde sigue insertar */ 
int  pq_size (pq *); 

#endif /* PRIORITYQUEUE_H_ */
