#ifndef KMEANS_CLUSTERING_KMEANS_OPENMP_H
#define KMEANS_CLUSTERING_KMEANS_OPENMP_H

#include <kmeans/clustering/kmeans.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the KMeans Algorithm using the OPENMP library.
 *
 * @param kmeans kmeans data structure.
 */
void KMeans_OpenMP_Execute(struct KMeans *kmeans);

#ifdef __cplusplus
}
#endif

#endif