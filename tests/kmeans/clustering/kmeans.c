#include <gtest/gtest.h>
#include <kmeans/clustering/kmeans.h>
#include <kmeans/clustering/cluster.h>
#include <kmeans/geometry/point.h>

TEST(KMeans, CreateEmptyDataSet)
{
	struct KMeans *kmeans = KMeans_Init(4);
	ASSERT_EQ(kmeans->numberPoints, 0);
	ASSERT_EQ(kmeans->k, 4);
	if (kmeans->points != NULL) FAIL();
	ASSERT_EQ(kmeans->clusters->size, 0);
	KMeans_Destroy(kmeans);
}

TEST(KMeans, CreateClusters)
{
	struct KMeans *kmeans = KMeans_Init(3);
	struct KM_Point **points = (struct KM_Point **) malloc(3 * sizeof(struct KM_Point));
	points[0] = KM_Point_Create(2, 2);
	points[1] = KM_Point_Create(5, 6);
	points[2] = KM_Point_Create(4, 8);
	KMeans_SetData(kmeans, points, 3);
	// Check centroids
	struct KM_Cluster *cluster1 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 0);
	struct KM_Cluster *cluster2 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 1);
	struct KM_Cluster *cluster3 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 2);

	ASSERT_EQ(cluster1->centroid->x, points[0]->x);
	ASSERT_EQ(cluster1->centroid->y, points[0]->y);

	ASSERT_EQ(cluster2->centroid->x, points[1]->x);
	ASSERT_EQ(cluster2->centroid->y, points[1]->y);

	ASSERT_EQ(cluster3->centroid->x, points[2]->x);
	ASSERT_EQ(cluster3->centroid->y, points[2]->y);

	KMeans_Destroy(kmeans);
}