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
	points[0] = KM_Point_Create(2, NULL);
	points[0]->coord[0] = 2;
	points[0]->coord[1] = 2;
	points[1] = KM_Point_Create(2, NULL);
	points[1]->coord[0] = 5;
	points[1]->coord[1] = 6;
	points[2] = KM_Point_Create(2, NULL);
	points[2]->coord[0] = 4;
	points[2]->coord[1] = 8;
	KMeans_SetData(kmeans, points, 3);
	// Check centroids
	struct KM_Cluster *cluster1 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 0);
	struct KM_Cluster *cluster2 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 1);
	struct KM_Cluster *cluster3 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 2);

	ASSERT_EQ(cluster1->centroid->coord[0], points[0]->coord[0]);
	ASSERT_EQ(cluster1->centroid->coord[1], points[0]->coord[1]);

	ASSERT_EQ(cluster2->centroid->coord[0], points[1]->coord[0]);
	ASSERT_EQ(cluster2->centroid->coord[1], points[1]->coord[1]);

	ASSERT_EQ(cluster3->centroid->coord[0], points[2]->coord[0]);
	ASSERT_EQ(cluster3->centroid->coord[1], points[2]->coord[1]);

	KMeans_Destroy(kmeans);
}

TEST(KMeans, GetClosestClusterToPoint)
{
	struct KMeans *kmeans = KMeans_Init(3);
	struct KM_Point **points = (struct KM_Point **) malloc(3 * sizeof(struct KM_Point));
	points[0] = KM_Point_Create(2, NULL);
	points[0]->coord[0] = 2;
	points[0]->coord[1] = 2;
	points[1] = KM_Point_Create(2, NULL);
	points[1]->coord[0] = 5;
	points[1]->coord[1] = 6;
	points[2] = KM_Point_Create(2, NULL);
	points[2]->coord[0] = 4;
	points[2]->coord[1] = 8;
	KMeans_SetData(kmeans, points, 3);
	
	struct KM_Cluster *cluster1 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 0);
	struct KM_Cluster *cluster2 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 1);
	struct KM_Cluster *cluster3 = (struct KM_Cluster*) KM_List_Get(kmeans->clusters, 2);

	struct KM_Cluster *closest = NULL;

	struct KM_Point *p = KM_Point_Create(2, NULL);
	p->coord[0] = 3;
	p->coord[1] = 5;
	closest = KMeans_FindClosestCluster(kmeans, p);
	ASSERT_EQ(closest, cluster2);

	p->coord[0] = -10;
	p->coord[1] = 0;
	closest = KMeans_FindClosestCluster(kmeans, p);
	ASSERT_EQ(closest, cluster1);

	p->coord[0] = 99;
	p->coord[1] = 80;
	closest = KMeans_FindClosestCluster(kmeans, p);
	ASSERT_EQ(closest, cluster3);
}