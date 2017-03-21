#include <kmeans/parser/parser.h>
#include <kmeans/parser/reader.h>
#include <kmeans/geometry/point.h>
#include <kmeans/clustering/kmeans.h>
#include <kmeans/collections/list.h>
#include <stdio.h>
#include <stdlib.h>

void StartExecution(const char *filename, unsigned long k)
{
    struct KM_FileReader *reader = KM_FileReader_Open(filename);
    struct KM_List *output = KM_List_Create();
    KM_Parser_Parse(reader, output);
    struct KMeans *kmeans = KMeans_Init(k);
    KMeans_SetData(kmeans, output);
    KMeans_Execute(kmeans, SEQUENTIAL);
    // for (i = 0; i < numberPoints; ++i) {
    //     printf("Point %lu: ", i+1);
    //     KM_Point_Print(&output[i]);
    // }
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Erro de uso do programa\nUso: kmeans <arquivo dataset> <numero clusters>\n");
        return -1;
    }
    unsigned long k = 0;
    const char *filename = argv[1];
    sscanf(argv[2], "%lu", &k);

    StartExecution(filename, k);

    return 0;
}