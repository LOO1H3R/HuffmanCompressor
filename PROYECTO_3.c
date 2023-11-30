#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pq.h"
#include "map.h"

/*

  gcc main.c map.c pq.c         COMPILAR 
  ./a.out                       CORRER

*/ 

typedef struct node
{
  int frequence;
  char letter;
  struct node * next;
  struct node * left;
  struct node * right;
  boolean parent;
}node;


/*Vincula los nodos por orden de salida, luego crea un nodo de suma y lo regresa*/
node * linking_nodes(node * left_child, node * right_child)
{
  node * father = malloc(sizeof(node));
  father->left = left_child;
  father->right = right_child;
  father->frequence = left_child->frequence + right_child->frequence;
  father->letter = '&';
  father->parent = TRUE;
  return father;
}

/* Generador del arbol de huffman, saca nodos de la pq e ingresa a la pq. Termina regresando la Raiz de arbol*/
node * huffman(pq * queue)
{
  node * first=NULL;
  node * second=NULL;
  node * new_node=NULL;
  int i=0;
  while(pq_size(queue) > 0)
    {
      i++;
      first = pq_poll(queue);
      second = pq_poll(queue);
      if(first != NULL && second != NULL)
      {
        new_node = linking_nodes(first, second);
        pq_offer(queue, new_node);
      }
      else if(first != NULL)
      {
        return first;
      }
      else if(second != NULL)
      {
        return second;
      }
    }
}


void *create_node(char letra)
  {
    node *new=malloc(sizeof(node));
    new->letter=letra;
    new->frequence=1;
    new->next=NULL;
    return new;
  }

void print_tabla(void *header)
{
  printf("\nTabla de frecuencias\n");
  node *print_p=(node*)header;
  while (print_p!=NULL)
    {
      printf("\nLetra:{%c} - Frecuencia: {%d}",print_p->letter,print_p->frequence);
      print_p=print_p->next;
    }
}

void *compare(void *text,void *cont)
  {
  char *p_text=(char*)text;
  int *cont2=(int*)cont;
  node * header=NULL;
  while (strcmp(p_text,"\0")!=0)
    {
      //printf("\nla letra es: {%c}\n",*p_text);
      
      if (header==NULL)
      {
       // printf("\nSe accedió a la creacion del primer nodo\n");
        node *new=(node*)create_node(*p_text);
        header=new;
        //printf("\nSe creó el primer nodo con letra {%c} y frecuencia {%d}\n",header->letter,header->frequence);
      }

      else if (header!=NULL)
      {
        //printf("\nYa existe un Header");
        node *var_p=header;
        node *before;
        while (var_p!=NULL)
          {
            //printf("\nSe revisa el nodo: {%c}\n",var_p->letter);
            if (var_p->letter==*p_text)
            {
              //printf("\nSe encontró la letra\n");
              var_p->frequence++;
              //printf("La frecuencia aumentó, está en: {%d}",var_p->frequence);
              break;
            }
            else
            {
              before=var_p;
              var_p=var_p->next;
            }
          }
        if (var_p==NULL)
          {
            //printf("Es una nueva letra, se crea un nuevo nodo");
            node *new=(node*)create_node(*p_text);
            before->next=new;
          }
      }
      *cont2=*cont2+1;
      p_text++;
    }
  return header;
  }

int compare_freq(void *a1, void*a2)
{
  node *aa1=(node*)a1;
  node *aa2=(node*)a2;
  return aa1->frequence-aa2->frequence;
}


int wordHash(void *t) {
	char *key = (char *)t;
	int i, hash = 0;
  hash = *key * 10;  
	return hash;
}

void print_inorder(node *n)
{
  if(n == NULL)
    return;
  print_inorder(n->left);
  printf("%d ", n->frequence);
  print_inorder(n->right);
}



boolean wordEquals(void * t1, void * t2) {
	char *c1 = (char *)t1;
	char *c2 = (char *)t2;
  if(*c1 == *c2)
  {
    return TRUE;
  }
  return FALSE;
	
}

/*recorrido tipo inOrder, recibe el diccionario a rellenar y añade los nodos tipo hoja TDA TIPO MAP*/

map * binary(node *n, char lado, char * binario,map * dictionary)
{
  char * codigo = "0";
  char * tmp = malloc(100);
  if(n == NULL)
  {
    return dictionary;
  }
  if(lado == 'l')
  {
    codigo = "0";
  }
  else if(lado == 'r'){
    codigo = "1";
  } 
  strcat(binario, codigo);
  strcpy(tmp,binario);
  binary(n->left, 'l', binario,dictionary);
  if(n->parent != TRUE)
  {
    printf("LETRA: %c   ||   FRECUENCIA: %d   ||   CODIGO BINARIO: %s \n", n->letter,n->frequence, tmp);
    map_put(dictionary,&(n->letter),tmp);
  }
  binary(n->right, 'r',tmp,dictionary);

  return dictionary;
}


//key son las letras, valor es el binario
char * printcompcad(map *nmap,char cadena[]){//Imprime la cadena comprimida
  char *value,cad;
  char * COMPRIMIDO = malloc(2000);
  int x=0;
  printf("%s = \n\n",cadena);
  while(cadena[x]!='\0'){
    cad = cadena[x];
    value = (char *)map_get(nmap,&cad);
    if(value==NULL){
      printf("_");
    }else{
      strcat(COMPRIMIDO, value);
      printf("%s",value);
    }
    x++;
  }
  printf("\n\nFIN DE LA COMPRESION\n\n");
  return COMPRIMIDO;
}

void uncompcad(map *nmap,node *header,char bincad[]){
  node *tmp = header;
  for(int x=1;bincad[x]!='\0';x++)
  {
    if(bincad[x]=='0')
        tmp=tmp->left;
    else if(bincad[x]=='1')
        tmp=tmp->right;
      
    if(tmp == NULL)
    { 
      tmp = header;
    }
    if(tmp->parent != TRUE)
    {
      printf("%c",tmp->letter);
    }
  }
  printf("\n\nFIN DE LA DESCOMPRESION\n\n");
}


int main(void) {

  //TEXTO
  char text[600]="Japan is the eleventh most populous country in the world, as well as one of the most densely populated and urbanized. About three-fourths of the country's terrain is mountainous, concentrating its population of 123.2 million on narrow coastal plains. Japan is divided into 47 administrative prefectures and eight traditional regions. The Greater Tokyo Area is the most populous metropolitan area in the world, with more than 35.6 million residents.";
  printf("\n\nTEXTO ORIGINAL: %s\n\n", text);

  //TABLA DE FRECUENCIA CON PRIORITY QUEUE
  char *text_p=text;
  int lent_text=0;
  int *lent_text_p=&lent_text;
  node * header=(node*)compare(text_p,lent_text_p);
  print_tabla(header);
  printf("\nFrecuencia total: {%d}\n",lent_text);
  pq * pq1= pq_create(lent_text,compare_freq);
  pq * pq2 = pq_create(lent_text,compare_freq);
  node *pq_p=header;
  while(pq_p!=NULL)
    {
      pq_offer(pq1,pq_p);
      pq_offer(pq2, pq_p);
      pq_p=pq_p->next;
    }


  //FRECUENCIAS ORDENADAS DE MENOR A MAYOR
  printf("\n\nTabla ordenada:\n");
  node *min;
  while(pq_size(pq1) > 0)
    {
      min = (node*) pq_poll(pq1);
      printf("\nPq: letra: {%c} freq: {%d}",min->letter,min->frequence);
    }   

  //ARBOL DE HUFFMAN
  node * huffman_tree = huffman(pq2);
  printf("\n\nHuffman tree impresion tipo inOrder: \n\n");
  print_inorder(huffman_tree);
  printf("\n\nRAIZ de HUFFMAN: %d \n\n", huffman_tree->frequence);

  //CODIGOS BINARIOS EN DICCIONARIO
  map * dictionary =  map_create(128,wordHash,wordEquals);
  char * binario = calloc(100,sizeof(char));
  printf("\nDICCIONARIO\n\n");
  binary(huffman_tree, 'N', binario, dictionary);
  

  //GENERACION DE CODIGO COMPRIMIDO
  printf("\nCADENA COMPRIMIDA\n\n");
  char * nuevo_binario = printcompcad(dictionary,text);

  //DESCOMPRESION DEL CODIGO BINARIO
  printf("\nDESCOMPRIMIENDO CADENA...\n\n");
  uncompcad(dictionary,huffman_tree,nuevo_binario);
  
}


/*

  gcc main.c map.c pq.c         COMPILAR 
  ./a.out                       CORRER

*/ 