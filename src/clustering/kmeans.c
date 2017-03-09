#include <kmeans/clustering/kmeans.h>
#include <kmeans/clustering/cluster.h>
#include <kmeans/clustering/kmeans_mpi.h>
#include <kmeans/clustering/kmeans_openmp.h>
#include <kmeans/clustering/kmeans_sequential.h>
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
void KMeans_SetData(struct KMeans *kmeans, struct KM_Point **points, unsigned long numberPoints)
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
 * Execute the algorithm with the data specified.
 *
 * @param kmeans kmeans data structure.
 * @param implementation implementation to be used.
 */
void KMeans_Execute(struct KMeans *kmeans, enum KM_Implementation implementation)
{
	/* THIS WILL EXECUTE AN ALGORITHM BASED ON WHICH IMPLEMENTATION
	IS CHOSEN */
	switch (implementation) {
		/*case MPI:
			KMeans_MPI_Execute(kmeans);
			break;
		case OPENMP:
			// KMeans_OpenMP_Execute(kmeans);
			break;*/
		case SEQUENTIAL:
			KMeans_Sequential_Execute(kmeans);
			break;
		default:
			break;
	}
}

/**
 * Finds the closest cluster from a point.
 *
 * @param kmeans kmeans data structure.
 * @param point point that will be compared to the clusters.
 * @return closer cluster to the point.
 */
struct KM_Cluster* KMeans_FindClosestCluster(struct KMeans *kmeans, struct KM_Point *point)
{
	double smallestDistance = 99999;
	struct KM_Cluster *closestCluster = NULL;
	struct KM_Cluster *currentCluster = NULL;
	double currentDistance = 0;
	unsigned int i = 0;
	for (; i < kmeans->clusters->size; ++i) {
		currentCluster = KM_List_Get(kmeans->clusters, i);
		currentDistance = KM_Point_GetDistance(currentCluster->centroid, point);
		if (currentDistance < smallestDistance) {
			smallestDistance = currentDistance;
			closestCluster = currentCluster;
		}
	}
	return closestCluster;
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