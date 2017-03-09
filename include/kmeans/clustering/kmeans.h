#ifndef KMEANS_CLUSTERING_KMEANS_H
#define KMEANS_CLUSTERING_KMEANS_H

#include <kmeans/collections/list.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enum that enumerates all available implementations
 * for the Kmeans algorithm.
 */
enum KM_Implementation {
	MPI,
	OPENMP,
	SEQUENTIAL,
};

/**
 * Structure that represents the KMeans algorithm data.
 */
struct KMeans {
	unsigned int k;
	struct KM_List *clusters;
	struct KM_Point **points;
	unsigned long numberPoints;
};

/**
 * Initialize a new KMeans experiment.
 *
 * @param k number of clusters.
 * @return pointer to the kmeans object.
 */
struct KMeans* KMeans_Init(unsigned int k);

/**
 * Define what data will be clustered by the algorithm.
 *
 * @param points array of points to be clustered.
 * @param numberPoints number of points in the array.
 */
void KMeans_SetData(struct KMeans *kmeans, struct KM_Point **points, unsigned long numberPoints);

/**
 * Execute the algorithm with the data specified.
 *
 * @param kmeans kmeans data structure.
 * @param implementation implementation to be used.
 */
void KMeans_Execute(struct KMeans *kmeans, enum KM_Implementation implementation);

/**
 * Finds the closest cluster from a point.
 *
 * @param kmeans kmeans data structure.
 * @param point point that will be compared to the clusters.
 * @return closer cluster to the point.
 */
struct KM_Cluster* KMeans_FindClosestCluster(struct KMeans *kmeans, struct KM_Point *point);

/**
 * Destroy a KMeans experiment.
 *
 * @param kmeans pointer to the Kmeans object.
 */
void KMeans_Destroy(struct KMeans *kmeans);

#ifdef __cplusplus
}
#endif

#endif