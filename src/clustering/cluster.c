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
	KM_Point_Destroy(cluster->centroid);
	free(cluster);
}

/**
 * Calculate the centroid of the cluster.
 *
 * @param cluster cluster that will be updated.
 */
void KM_Cluster_UpdateCentroid(struct KM_Cluster *cluster)
{
	struct KM_Point *point = point = KM_List_Get(cluster->points, 0);;
	unsigned int currentPoint = 0;
	unsigned int dimensions = point->dimensions;
	unsigned int currentDimension = 0;
	double *sum = malloc(sizeof(double) * dimensions);

	for (; currentPoint < cluster->points->size; ++currentPoint) {
		point = KM_List_Get(cluster->points, currentPoint);
		for (currentDimension = 0; currentDimension < dimensions; ++currentDimension) {
			sum[currentDimension] += point->coord[currentDimension];
		}
	}

	/* Calculate mean out of sum */
	for (currentDimension = 0; currentDimension < dimensions; ++currentDimension) {
		sum[currentDimension] = (sum[currentDimension] / cluster->points->size);
	}

	if (cluster->centroid != NULL)
		KM_Point_Destroy(cluster->centroid);
	cluster->centroid = KM_Point_Create(dimensions, sum);
	free(sum);
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

/**
 * Clone the cluster, but doesn't clone its points.
 *
 * @param cluster cluster to be cloned.
 * @return pointer to the new cluster.
 */
struct KM_Cluster* KM_Cluster_Clone(struct KM_Cluster *cluster)
{
	struct KM_Cluster *clone = KM_Cluster_Create();
	clone->centroid = KM_Point_Clone(cluster->centroid);
	return clone;
}