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
	struct KM_Point *p1 = KM_Point_Create(2, NULL);
	p1->coord[0] = 6;
	p1->coord[1] = 3;
	struct KM_Point *p2 = KM_Point_Create(2, NULL);
	p2->coord[0] = 5;
	p2->coord[1] = 10;
	struct KM_Point *p3 = KM_Point_Create(2, NULL);
	p3->coord[0] = 7;
	p3->coord[1] = 2;
	KM_Cluster_AddPoint(cluster, p1);
	KM_Cluster_AddPoint(cluster, p2);
	KM_Cluster_AddPoint(cluster, p3);
	KM_Cluster_UpdateCentroid(cluster);
	ASSERT_DOUBLE_EQ(cluster->centroid->coord[0], 6.0);
	ASSERT_DOUBLE_EQ(cluster->centroid->coord[1], 5.0);
	KM_Point_Destroy(p1);
	KM_Point_Destroy(p2);
	KM_Point_Destroy(p3);
	KM_Cluster_Destroy(cluster);
}