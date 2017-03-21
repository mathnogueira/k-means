#ifndef KMEANS_CLUSTERING_KMEANS_H
#define KMEANS_CLUSTERING_KMEANS_H

#include <kmeans/collections/list.h>
#include <kmeans/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enum that enumerates all available implementations
 * for the Kmeans algorithm.
 */
enum KM_Implementation {
	SEQUENTIAL = 1,
	OPENMP,
	MPI,
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
 * @param kmeans kmeans set of clusters.
 * @param points list of points to be clustered.
 */
void KMeans_SetData(struct KMeans *kmeans, struct KM_List *points);

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
 * Verify if two set of clusters have converged.
 *
 * @param set1 first set of clusters.
 * @param set2 second set of clusters.
 * @return true if all centroids of set1 and set2 are the same.
 */
bool KMeans_ClustersHaveConverged(struct KMeans *set1, struct KMeans *set2);

/**
 * Destroy all points inside all clusters, but keep the centroid.
 *
 * @param kmeans cluster set to be reseted.
 */
void KMeans_ResetPoints(struct KMeans *kmeans);

/**
 * Clone all clusters ignoring its points.
 *
 * @param kmeans kmeans cluster set.
 * @return pointer to the clone kmeans set.
 */
struct KMeans* KMeans_Clone(struct KMeans *kmeans);

void KMeans_PrintResult(struct KMeans *kmeans);

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