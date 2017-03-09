#ifndef KMEANS_CLUSTERING_KMEANS_MPI_H
#define KMEANS_CLUSTERING_KMEANS_MPI_H

#include <kmeans/clustering/kmeans.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Execute the KMeans Algorithm using the MPI library.
 *
 * @param kmeans kmeans data structure.
 */
void KMeans_MPI_Execute(struct KMeans *kmeans);

#ifdef __cplusplus
}
#endif

#endif