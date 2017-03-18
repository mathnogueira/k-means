#include <gtest/gtest.h>
#include <kmeans/geometry/point.h>

TEST(Point, CalculateDistanceSamePoint)
{
    struct KM_Point* point1 = KM_Point_Create(2, NULL);
    struct KM_Point* point2 = KM_Point_Create(2, NULL);
    point1->coord[0] = 2;
    point1->coord[1] = 2;
    point2->coord[0] = 2;
    point2->coord[1] = 2;

    double distance = KM_Point_GetDistance(point1, point2);
    ASSERT_EQ(distance, 0);
}

TEST(Point, CalculateDistance)
{
    struct KM_Point* point1 = KM_Point_Create(2, NULL);
    struct KM_Point* point2 = KM_Point_Create(2, NULL);
    point1->coord[0] = 3;
    point1->coord[1] = 6;
    point2->coord[0] = 6;
    point2->coord[1] = 2;

    double distance = KM_Point_GetDistance(point1, point2);
    ASSERT_EQ(distance, 5);
}