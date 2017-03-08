#ifndef KMEANS_CLUSTERING_CLUSTER_H
#define KMEANS_CLUSTERING_CLUSTER_H

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Structure that represents a k-means cluster.
 */
struct KM_Cluster {
	void *points;
};

#ifdef __cplusplus
}
#endif

#endif