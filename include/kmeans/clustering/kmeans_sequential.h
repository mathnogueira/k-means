#ifndef KMEANS_CLUSTERING_KMEANS_SEQUENTIAL_H
#define KMEANS_CLUSTERING_KMEANS_SEQUENTIAL_H

#include <kmeans/clustering/kmeans.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the KMeans Algorithm using the OPENMP library.
 *
 * @param kmeans kmeans data structure.
 */
void KMeans_Sequential_Execute(struct KMeans *kmeans);

#ifdef __cplusplus
}
#endif

#endif