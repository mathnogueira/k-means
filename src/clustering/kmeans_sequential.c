#include <kmeans/clustering/kmeans.h>
#include <kmeans/clustering/kmeans_sequential.h>
#include <kmeans/clustering/cluster.h>
#include <stdlib.h>

/**
 * Execute the KMeans Algorithm using the OPENMP library.
 *
 * @param kmeans kmeans data structure.
 */
void KMeans_Sequential_Execute(struct KMeans *kmeans)
{
	/* http://codereview.stackexchange.com/questions/128315/k-means-clustering-algorithm-implementation */
	struct KMeans *previous = NULL;
	unsigned long i = 0;
	unsigned long numberPoints = kmeans->numberPoints;
	unsigned int numberClusters = kmeans->k;
	do {
		previous = KMeans_Clone(kmeans);
		KMeans_ResetPoints(kmeans);
		for (i = 0; i < numberPoints; ++i) {
			struct KM_Point *point = kmeans->points[i];
			struct KM_Cluster *closestCluster = KMeans_FindClosestCluster(kmeans, point);
			KM_Cluster_AddPoint(closestCluster, point);
		}
		for (i = 0; i < numberClusters; ++i) {
			struct KM_Cluster *cluster = KM_List_Get(kmeans->clusters, i);
			KM_Cluster_UpdateCentroid(cluster);
		}
	} while (!KMeans_ClustersHaveConverged(kmeans, previous));
}