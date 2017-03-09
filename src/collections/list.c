#include <kmeans/collections/list.h>
#include <stdlib.h>

/* Node declaration. */
struct KM_List_Node {
	struct KM_List_Node *next;
	struct KM_List_Node *prev;
	void *element;
};

struct KM_List_Node* KM_List_Node_Create(void *element, struct KM_List_Node *next)
{
	struct KM_List_Node *node = (struct KM_List_Node*) malloc(sizeof(struct KM_List_Node));
	node->element = element;
	node->next = next;
	node->prev = NULL;
	return node;
}

void KM_List_Node_Destroy(struct KM_List_Node *node)
{
	free(node);
}

/**
 * Create a new empty list.
 *
 * @return pointer to the new list.
 */
struct KM_List* KM_List_Create()
{
	struct KM_List *list = (struct KM_List*) malloc(sizeof(struct KM_List));
	list->head = NULL;
	list->size = 0;
	return list;
}

/**
 * Destroy a list. It will cause memory leak if you dont remove all elements inside the list
 * before calling this function.
 *
 * @param container list that will be destroyed.
 */
void KM_List_Destroy(struct KM_List *container)
{
	while (container->size > 0) {
		KM_List_Remove(container, 0);
	}
	free(container);
}

/**
 * Add a new element to the list.
 *
 * @param container list that will store the value.
 * @param value element that will be added to the list.
 */
void KM_List_Add(struct KM_List *container, void *value)
{
	/* Sorry Linus, I failed you =/ */
	struct KM_List_Node *node = KM_List_Node_Create(value, NULL);
	if (container->head == NULL) {
		container->head = node;
	} else {
		struct KM_List_Node *current;
		for (current = container->head; current->next != NULL; current = current->next);
		current->next = node;
		node->prev = current;
	}
	container->size++;
}

/**
 * Remove element from list and return it.
 *
 * @param container list that contains the element that will be removed.
 * @param position position where the element is inside the list.
 */
void* KM_List_Remove(struct KM_List *container, unsigned int position)
{
	if (container->size <= position)
		return NULL;
	struct KM_List_Node *current = container->head;
	void *element = NULL;
	unsigned int cPos = 0;
	while (cPos++ < position) {
		current = current->next;
	}
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	if (current == container->head)
		container->head = current->next;
	element = current->element;
	KM_List_Node_Destroy(current);
	container->size--;
	return element;
}

	/**
	 * Retrieve the element at position.
	 *
	 * @param container list that stores the element.
	 * @param position position where the element is inside the list.
	 * @return element at position specified.
	 */
	void* KM_List_Get(struct KM_List *container, unsigned int position)
	{
		if (container->size <= position)
			return NULL;
		struct KM_List_Node *current = container->head;
		void *element = NULL;
		unsigned int cPos = 0;
		while (cPos++ < position) {
			current = current->next;
		}
		return current->element;
	}