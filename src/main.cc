#include <kmeans/parser/parser.h>
#include <kmeans/parser/reader.h>
#include <kmeans/geometry/point.h>
#include <kmeans/clustering/kmeans.h>
#include <stdio.h>
#include <stdlib.h>

void StartExecution(const char *filename, unsigned long k)
{
    struct KM_FileReader *reader = KM_FileReader_Open(filename);
    struct KM_Point *output = NULL;
    unsigned long numberPoints = 0;
    KM_Parser_Parse(reader, &output, &numberPoints);
    struct KMeans *kmeans = KMeans_Init(k);
    KMeans_SetData(kmeans, &output, numberPoints);
    KMeans_Execute(kmeans, SEQUENTIAL);
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