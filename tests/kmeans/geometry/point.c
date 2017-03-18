#include <gtest/gtest.h>
#include <kmeans/geometry/point.h>

TEST(Point, CalculateDistanceSamePoint)
{
    struct KM_Point *point1 = KM_Point_Create(2, NULL);
    struct KM_Point *point2 = KM_Point_Create(2, NULL);
    point1->coord[0] = 2;
    point1->coord[1] = 2;
    point2->coord[0] = 2;
    point2->coord[1] = 2;

    double distance = KM_Point_GetDistance(point1, point2);
    ASSERT_EQ(distance, 0);
    KM_Point_Destroy(point1);
    KM_Point_Destroy(point2);
}

TEST(Point, CalculateDistance)
{
    struct KM_Point *point1 = KM_Point_Create(2, NULL);
    struct KM_Point *point2 = KM_Point_Create(2, NULL);
    point1->coord[0] = 3;
    point1->coord[1] = 6;
    point2->coord[0] = 6;
    point2->coord[1] = 2;

    double distance = KM_Point_GetDistance(point1, point2);
    ASSERT_EQ(distance, 5);
    KM_Point_Destroy(point1);
    KM_Point_Destroy(point2);
}

TEST(Point, Clone)
{
    struct KM_Point *point = KM_Point_Create(2, NULL);
    point->coord[0] = 3;
    point->coord[1] = 6;
    struct KM_Point *clone = KM_Point_Clone(point);
    ASSERT_FALSE(clone->coord == point->coord);
    
    for (unsigned int i = 0; i < point->dimensions; ++i) {
        ASSERT_DOUBLE_EQ(clone->coord[i], point->coord[i]);
    }

    KM_Point_Destroy(point);
    KM_Point_Destroy(clone);
}