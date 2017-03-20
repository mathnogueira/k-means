#include <kmeans/parser/parser.h>
#include <kmeans/geometry/point.h>
#include <kmeans/collections/list.h>
#include <string.h>
#include <stdio.h>

struct KM_Point* GetPointFromString(char *string)
{
    char *pch = strtok(string, ",");
    struct KM_List *list = KM_List_Create();
    unsigned int dbg = 0;
    while (pch != NULL) {
        double *coord = malloc(sizeof(double));
        sscanf(pch, "%lf", coord);
        KM_List_Add(list, coord);
        pch = strtok(NULL, ",");
    }
    double *array = NULL;
    unsigned long size = (list->size)-1;

    double *classificationPtr = KM_List_Remove(list, size);
    double classification = *classificationPtr;
    free(classificationPtr);
    KM_LIST_TOARRAY(list, array, double);
    while (list->size > 0) {
        free(KM_List_Remove(list, 0));
    }
    KM_List_Destroy(list);
    return KM_Point_Create(size, array);
}

/**
 * Parse a data file and return an array of points out of it.
 *
 * @param file file to be parsed.
 * @param output array that will be used as output of the parser.
 */
void KM_Parser_Parse(struct KM_FileReader *file, struct KM_Point **output)
{
    char line[4096];
    struct KM_List *list = KM_List_Create();
    while (KM_FileReader_ReadLine(line, file)) {
        struct KM_Point *point = GetPointFromString(line);
        KM_List_Add(list, point);
    }

    *output = (struct KM_Point*) malloc(sizeof(struct KM_Point) * list->size);
    do {															
		unsigned int size = (list)->size;						
		unsigned int i = 0;											
		*output = (struct KM_Point*) malloc(sizeof(struct KM_Point) * size);				
		for (; i < size; ++i) {										
			(*output)[i] = *((struct KM_Point*) KM_List_Get(list, i));		
		}															
	} while (0);
}