#include "map.h"
#include <stdlib.h>
#include <stdio.h>

struct node_str {
	void * key, * value;
	struct node_str * next;
};

typedef struct node_str node;

struct map_str {
	hash_func hash;
	equals_func key_equals;
	int M, size;
	node ** hashTable;
};

/* allocates and initialize the map structure */
map * map_create(int M, hash_func hf, equals_func ke) 
{
  map * m = (map *) malloc(sizeof(struct map_str));
	m->M = M;
	m->hash = hf;
	m->key_equals = ke;
	m->size = 0;
	m->hashTable = (node **) malloc(M * sizeof(node * ));
	
	for(int i = 0; i < M ; i ++) 
    m->hashTable[i] = NULL;
	return m;
}

/* returns the size of the map (current number of key inserted) */
int map_size (map * m) 
{
	return m->size;
}

/* function to create (allocate) and initialize nodes */
node * createNode(void * key, void * value) {
	node * n = (node *) malloc(sizeof(struct node_str));
	n->key = key;
	n->value = value;
	n->next = NULL;
	return n;
}

void map_put(map * m, void * key, void * value)
{
  /* Search for an already existing key */
  int hash = m->hash(key) % m->M;
	node * n = m->hashTable[hash];
  //printf("HASH ADAPTADO = %d ", hash);
  //printf("HOLAAAA");
	while(n != NULL) 
  {
   // printf("ADIOOOSS");
    /* for any key found, see if its the one we want to put,
       if found, just break, if not continue searching until
       we get to the end of the linked list inside this bucket */
    if(m->key_equals(n->key, key)) 
      break;
    else
      n = n->next;
	}

  /* here we have traversed the list, n will either be NULL if
     no key was found or have an address value if it does */
	if(n != NULL) 
  {
    /* key already existed, update its value */
		n->value = value;
		return;
	}

  /* this handle the case of the key not existing in the table,
    we need to add it at the end of the linked list */
  n = m->hashTable[hash];
  
	if(n == NULL) 
  {
    /* case: the bucket is empty */
    //printf("original %d\n\n",m->size);
    //printf("BUCKET EMPTY\n\n");
		m->hashTable[hash] = createNode(key, value);
		m->size++;
  //  printf("incrementa %d\n\n",m->size);
	} 
  else 
  {
    /* case: the key hit a collision, more elements might live in
      this bucket, go to the end of the list and add it there */
   // printf("BUCKET FULL\n\n");
		while(n->next != NULL) 
    {
      n = n->next;
    }
		n->next = createNode(key, value);
		m->size ++;
	}
}

boolean map_contains(map *m, void * key) 
{
  /* returns TRUE if the map contains the key */
  int hash = m->hash(key) % m->M;
	node * n = m->hashTable[hash];
	while(n != NULL) 
  {
    if(m->key_equals(n->key, key)) 
      return TRUE;
    else
      n = n->next;
	}
	return FALSE;
}

void * map_get(map *m, void *key) 
{
  /* search for the key in the table:
    step 1: find the bucket, with the hash function.
    step 2: traverse the linked list inside the bucket until element
            is found, return the stored value if we do. 
            Return NULL if we get to the end of the list */
  
  int hash = m->hash(key) % m->M;
	node * n = m->hashTable[hash];
	while(n != NULL) 
  {
    if(m->key_equals(n->key, key)) 
      break;
    else
      n = n->next;
	}
	return n != NULL ? n->value : NULL;
}