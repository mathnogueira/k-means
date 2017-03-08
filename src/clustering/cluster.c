#include <kmeans/clustering/cluster.h>
#include <kmeans/geometry/point.h>
#include <stdlib.h>

/**
 * Create a new empty cluster.
 *
 * @return pointer to the cluster.
 */
struct KM_Cluster* KM_Cluster_Create()
{
	struct KM_Cluster *cluster = (struct KM_Cluster*) malloc(sizeof(struct KM_Cluster));
	cluster->points = KM_List_Create();
	cluster->centroid = NULL;
	return cluster;
}

/**
 * Destroy a cluster.
 *
 * @param cluster cluster that will be destroyed.
 */
void KM_Cluster_Destroy(struct KM_Cluster *cluster)
{
	KM_List_Destroy(cluster->points);
	free(cluster);
}

/**
 * Calculate the centroid of the cluster.
 *
 * @param cluster cluster that will be updated.
 */
void KM_Cluster_UpdateCentroid(struct KM_Cluster *cluster)
{
	struct KM_Point *point = NULL;
	unsigned int currentPoint = 0;
	double sumX = 0;
	double sumY = 0;
	for (; currentPoint < cluster->points->size; currentPoint++) {
		point = (struct KM_Point*) KM_List_Get(cluster->points, currentPoint);
		sumX += point->x;
		sumY += point->y;
	}
	if (cluster->centroid != NULL)
		KM_Point_Destroy(cluster->centroid);
	cluster->centroid = KM_Point_Create(sumX / cluster->points->size, sumY / cluster->points->size);
}

/**
 * Add point to the cluster.
 *
 * @param cluster cluster where the point will be added.
 * @param point point to be added to the cluster.
 */
void KM_Cluster_AddPoint(struct KM_Cluster *cluster, struct KM_Point *point)
{
	KM_List_Add(cluster->points, point);
}