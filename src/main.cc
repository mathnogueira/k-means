#include <kmeans/parser/parser.h>
#include <kmeans/parser/reader.h>
#include <kmeans/geometry/point.h>
#include <kmeans/clustering/kmeans.h>
#include <kmeans/collections/list.h>
#include <stdio.h>
#include <stdlib.h>

void StartExecution(const char *filename, unsigned long k, KM_Implementation implementation)
{
    struct KM_FileReader *reader = KM_FileReader_Open(filename);
    struct KM_List *output = KM_List_Create();
    KM_Parser_Parse(reader, output);
    struct KMeans *kmeans = KMeans_Init(k);
    KMeans_SetData(kmeans, output);
    /*KMeans_PrintResult(kmeans);*/
    KMeans_Execute(kmeans, implementation);
    /*KMeans_PrintResult(kmeans);*/
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Erro de uso do programa\nUso: kmeans <arquivo dataset> <numero clusters> <implementacao (1=sequencial, 2=openmp)>\n");
        return -1;
    }
    KM_Implementation implementation = SEQUENTIAL;
    unsigned long k = 0;
    const char *filename = argv[1];
    sscanf(argv[2], "%lu", &k);
    if (argc == 4) {
        int impl = 0;
        sscanf(argv[3], "%d", &impl);
        implementation = (KM_Implementation) impl;
    }

    StartExecution(filename, k, implementation);

    return 0;
}