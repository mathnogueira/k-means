#ifndef KMEANS_CLUSTERING_KMEANS_H
#define KMEANS_CLUSTERING_KMEANS_H

#include <kmeans/collections/list.h>

#ifdef __cplusplus
extern "C" {
#endif

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
void KMeans_SetData(struct KMeans* kmeans, struct KM_Point **points, unsigned long numberPoints);

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