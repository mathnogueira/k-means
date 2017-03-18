#ifndef KMEANS_CLUSTERING_CLUSTER_H
#define KMEANS_CLUSTERING_CLUSTER_H

#include <kmeans/collections/list.h>
#include <kmeans/geometry/point.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Structure that represents a k-means cluster.
 */
struct KM_Cluster {
	struct KM_List *points;
	struct KM_Point *centroid;
};

/**
 * Create a new empty cluster.
 *
 * @return pointer to the cluster.
 */
struct KM_Cluster* KM_Cluster_Create();

/**
 * Destroy a cluster.
 *
 * @param cluster cluster that will be destroyed.
 */
void KM_Cluster_Destroy(struct KM_Cluster *cluster);

/**
 * Calculate the centroid of the cluster.
 *
 * @param cluster cluster that will be updated.
 */
void KM_Cluster_UpdateCentroid(struct KM_Cluster *cluster);

/**
 * Add point to the cluster.
 *
 * @param cluster cluster where the point will be added.
 * @param point point to be added to the cluster.
 */
void KM_Cluster_AddPoint(struct KM_Cluster *cluster, struct KM_Point *point);

/**
 * Clone the cluster, but doesn't clone its points.
 *
 * @param cluster cluster to be cloned.
 * @return pointer to the new cluster.
 */
struct KM_Cluster* KM_Cluster_Clone(struct KM_Cluster *cluster);

#ifdef __cplusplus
}
#endif

#endif