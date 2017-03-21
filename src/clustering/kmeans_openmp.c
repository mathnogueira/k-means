#include <kmeans/clustering/kmeans.h>
#include <kmeans/clustering/kmeans_openmp.h>
#include <kmeans/clustering/cluster.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

/**
 * Execute the KMeans Algorithm using the OPENMP library.
 *
 * @param kmeans kmeans data structure.
 */
void KMeans_OpenMP_Execute(struct KMeans *kmeans)
{
	printf("RUNNING OPENMP\n");
	/* http://codereview.stackexchange.com/questions/128315/k-means-clustering-algorithm-implementation */
	struct KMeans *previous = NULL;
	unsigned long i = 0;
	unsigned long numberPoints = kmeans->numberPoints;
	unsigned int numberClusters = kmeans->k;
	struct KM_Point **points = kmeans->points;
	do {
		previous = KMeans_Clone(kmeans);
		KMeans_ResetPoints(kmeans);
		#pragma omp parallel for num_threads(omp_get_num_procs())
		for (i = 0; i < numberPoints; ++i) {
			struct KM_Point *point = points[i];
			struct KM_Cluster *closestCluster = KMeans_FindClosestCluster(kmeans, point);
			KM_Cluster_AddPoint(closestCluster, point);
		}

		for (i = 0; i < numberClusters; ++i) {
			struct KM_Cluster *cluster = KM_List_Get(kmeans->clusters, i);
			if (cluster->points->size > 0)
				KM_Cluster_UpdateCentroid(cluster);
		}
	} while (!KMeans_ClustersHaveConverged(kmeans, previous));
}