#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct HashMap HashMap;
int enlarge_called=0;
struct HashMap 
{
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) 
{
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash(char * key, long capacity) 
{
    unsigned long hash = 0;
    char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) 
    {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2)
{
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) 
{
    long clave = hash(key, map->capacity);
    if (map->buckets[clave]->value != NULL && map->buckets[clave]->key != NULL)
    {
        map->buckets[clave]->key = key;
        map->buckets[clave]->value = value;
        map->current = clave;
    }
    else
    {
        for (int i = clave ; i < map->capacity ; i = i + 1)//Hacer un while y ir comparando el current con la clave a la que se ingreso
        {
            if (map->buckets[i]->value != NULL && map->buckets[i]->key != NULL)
            {
                map->buckets[clave]->key = key;
                map->buckets[clave]->value = value;
                map->current = i;
                break;
            }
        }
    }
    map->size = map->size + 1;
}

void enlarge(HashMap * map) 
{
    enlarge_called = 1; //no borrar (testing purposes)
}


HashMap * createMap(long capacity) 
{
    HashMap* tmp = (HashMap*) calloc (capacity, sizeof(HashMap));
    tmp->buckets = (Pair**) calloc (capacity, sizeof(Pair*));
    tmp->capacity = capacity;
    tmp->size = 0;
    tmp->current = -1;
    return tmp;
}

void eraseMap(HashMap * map,  char * key) 
{    


}

Pair * searchMap(HashMap * map,  char * key) 
{   
    long clave = hash(key, map->capacity);
    if (is_equal(map->buckets[clave]->key, key) == 1)
    {
        return (map->buckets[clave]->value);
    }

    return NULL;
}

Pair * firstMap(HashMap * map) 
{

    return NULL;
}

Pair * nextMap(HashMap * map) 
{

    return NULL;
}
