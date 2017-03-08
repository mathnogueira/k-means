#include <gtest/gtest.h>
#include <kmeans/clustering/cluster.h>

TEST(Cluster, CreateEmptyCluster)
{
	struct KM_Cluster *cluster = KM_Cluster_Create();
	ASSERT_EQ(cluster->points->size, 0);
	KM_Cluster_Destroy(cluster);
}

TEST(Cluster, CalculateCentoid)
{
	struct KM_Cluster *cluster = KM_Cluster_Create();
	struct KM_Point *p1 = KM_Point_Create(6, 3);
	struct KM_Point *p2 = KM_Point_Create(5, 10);
	struct KM_Point *p3 = KM_Point_Create(7, 2);
	KM_Cluster_AddPoint(cluster, p1);
	KM_Cluster_AddPoint(cluster, p2);
	KM_Cluster_AddPoint(cluster, p3);
	KM_Cluster_UpdateCentroid(cluster);
	ASSERT_DOUBLE_EQ(cluster->centroid->x, 6.0);
	ASSERT_DOUBLE_EQ(cluster->centroid->y, 5.0);
	KM_Point_Destroy(p1);
	KM_Point_Destroy(p2);
	KM_Point_Destroy(p3);
	KM_Cluster_Destroy(cluster);
}