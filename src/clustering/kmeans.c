#include <kmeans/clustering/kmeans.h>
#include <kmeans/clustering/cluster.h>
#include <stdlib.h>

/**
 * Initialize a new KMeans experiment.
 *
 * @param k number of clusters.
 * @return pointer to the kmeans object.
 */
struct KMeans* KMeans_Init(unsigned int k)
{
	struct KMeans *kmeans = (struct KMeans*) malloc(sizeof(struct KMeans));
	kmeans->k = k;
	kmeans->clusters = KM_List_Create();
	kmeans->points = NULL;
	kmeans->numberPoints = 0;
	return kmeans;
}

/**
 * Define what data will be clustered by the algorithm.
 *
 * @param kmeans kmeans structure.
 * @param points array of points to be clustered.
 * @param numberPoints number of points in the array.
 */
void KMeans_SetData(struct KMeans* kmeans, struct KM_Point **points, unsigned long numberPoints)
{
	unsigned int i = 0;
	struct KM_Cluster *cluster = NULL;
	struct KM_Point *point = NULL;
	/* Use the K first points as centroids */
	for (; i < kmeans->k; ++i) {
		cluster = KM_Cluster_Create();
		point = points[i];
		KM_Cluster_AddPoint(cluster, point);
		KM_Cluster_UpdateCentroid(cluster);
		KM_List_Add(kmeans->clusters, cluster);
	}
	kmeans->points = points;
	kmeans->numberPoints = numberPoints;
}

/**
 * Destroy a KMeans experiment.
 *
 * @param kmeans pointer to the Kmeans object.
 */
void KMeans_Destroy(struct KMeans *kmeans)
{
	struct KM_Cluster *cluster = NULL;
	unsigned long i = 0;
	while (kmeans->clusters->size > 0) {
		cluster = (struct KM_Cluster*) KM_List_Remove(kmeans->clusters, 0);
		KM_Cluster_Destroy(cluster);
	}
	for (; i < kmeans->numberPoints; ++i) {
		KM_Point_Destroy(kmeans->points[i]);
	}
	KM_List_Destroy(kmeans->clusters);
	free(kmeans->points);
	free(kmeans);
}