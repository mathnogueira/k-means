#ifndef KMEANS_COLLECTIONS_LIST_H
#define KMEANS_COLLECTIONS_LIST_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
/* Forward declaration for node */
struct KM_List_Node;

/**
 * Structure that represents a list structure.
 */
struct KM_List {
	struct KM_List_Node *head;
	unsigned int size;
};

/**
 * Create a new empty list.
 *
 * @return pointer to the new list.
 */
struct KM_List* KM_List_Create();

/**
 * Destroy a list. It will cause memory leak if you dont remove all elements inside the list
 * before calling this function.
 *
 * @param container list that will be destroyed.
 */
void KM_List_Destroy(struct KM_List *container);

/**
 * Add a new element to the list.
 *
 * @param container list that will store the value.
 * @param value element that will be added to the list.
 */
void KM_List_Add(struct KM_List *container, void *value);

/**
 * Remove element from list and return it.
 *
 * @param container list that contains the element that will be removed.
 * @param position position where the element is inside the list.
 * @return element removed
 */
void* KM_List_Remove(struct KM_List *container, unsigned int position);

/**
 * Retrieve the element at position.
 *
 * @param container list that stores the element.
 * @param position position where the element is inside the list.
 * @return element at position specified.
 */
void* KM_List_Get(struct KM_List *container, unsigned int position);

/**
 * Transform a list into an array.
 *
 * @param container list to be converted.
 * @param output pointer to the array that will be allocated and populated.
 * @param dataSize size of each element of the array.
 */
#define KM_LIST_TOARRAY(CONTAINER, OUTPUT, TYPE) { 					\
	do {															\
		unsigned int size = (CONTAINER)->size;						\
		unsigned int i = 0;											\
		OUTPUT = (TYPE*) malloc(sizeof(TYPE) * size);				\
		for (; i < size; ++i) {										\
			OUTPUT[i] = *((TYPE*) KM_List_Get(CONTAINER, i));		\
		}															\
	} while (0);													\
}

#ifdef __cplusplus
}
#endif

#endif