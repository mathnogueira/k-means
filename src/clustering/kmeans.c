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
 * @param points list of points to be clustered.
 */
void KMeans_SetData(struct KMeans *kmeans, struct KM_List *points)
{
	unsigned long i = 0;
	struct KM_Cluster *cluster = NULL;
	struct KM_Point *point = NULL;
	/* Use the K first points as centroids */
	for (; i < kmeans->k; ++i) {
		cluster = KM_Cluster_Create();
		point = KM_List_Get(points, i);
		KM_Cluster_AddPoint(cluster, point);
		KM_Cluster_UpdateCentroid(cluster);
		KM_List_Add(kmeans->clusters, cluster);
	}
	struct KM_Point **pointsArray = (struct KM_Point**) malloc(sizeof(struct KM_Point*) * points->size);
	for (i = 0; i < points->size; ++i) {
		pointsArray[i] = (struct KM_Point*) KM_List_Get(points, i);
	}
	kmeans->points = pointsArray;
	kmeans->numberPoints = points->size;
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

/**
 * Verify if two set of clusters have converged.
 *
 * @param set1 first set of clusters.
 * @param set2 second set of clusters.
 * @return true if all centroids of set1 and set2 are the same.
 */
bool KMeans_ClustersHaveConverged(struct KMeans *set1, struct KMeans *set2)
{
	bool converged = true;
	unsigned int i = 0;
	struct KM_Cluster *cluster1 = NULL;
	struct KM_Cluster *cluster2 = NULL;
	while (converged && i < set1->clusters->size) {
		cluster1 = KM_List_Get(set1->clusters, i);
		cluster2 = KM_List_Get(set2->clusters, i);
		converged &= KM_Point_Equals(cluster1->centroid, cluster2->centroid);
		++i;
	}
	return converged;
}

/**
 * Destroy all points inside all clusters, but keep the centroid.
 *
 * @param kmeans cluster set to be reseted.
 */
void KMeans_ResetPoints(struct KMeans *kmeans)
{
	unsigned int numberClusters = kmeans->k;
	unsigned int i = 0;
	struct KM_Cluster *cluster = NULL;
	for (; i < numberClusters; ++i) {
		cluster = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, i);
		KM_Cluster_ResetPoints(cluster);
	}
}

/**
 * Clone all clusters ignoring its points.
 *
 * @param kmeans kmeans cluster set.
 * @return pointer to the clone kmeans set.
 */
struct KMeans* KMeans_Clone(struct KMeans *kmeans)
{
	struct KMeans *clone = KMeans_Init(kmeans->k);
	unsigned int numberClusters = kmeans->clusters->size;
	unsigned int i = 0;
	for (; i < numberClusters; ++i) {
		struct KM_Cluster *cluster = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, i);
		KM_List_Add(clone->clusters, KM_Cluster_Clone(cluster));
	}
	return clone;
}