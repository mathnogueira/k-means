#include <kmeans/geometry/point.h>
#include <stdlib.h>
#include <math.h>

/**
 * Create a new point.
 *
 * @param x x coordinate.
 * @param y y coordinate.
 * @return pointer to the point.
 */
struct KM_Point* Point(double x, double y)
{
	struct KM_Point *point = (struct KM_Point*) malloc(sizeof(struct KM_Point));
	point->x = x;
	point->y = y;
	return point;
}

/**
 * Destroy a point.
 *
 * @param point point to be destroyed.
 */
void Free_Point(struct KM_Point *point)
{
	free(point);
}

/**
 * Calculate the distance from two points.
 *
 * @param p1 origin point
 * @param p2 destination point
 * @return distance from p1 to p2
 */
double KM_Point_GetDistance(struct KM_Point *p1, struct KM_Point *p2)
{
	return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}