#ifndef KMEANS_GEOMETRY_POINT_H
#define KMEANS_GEOMETRY_POINT_H

/**
 * Struct that represents a point in the algorithm.
 */
struct KM_Point {
	double x;
	double y;
};

/**
 * Create a new point.
 *
 * @param x x coordinate.
 * @param y y coordinate.
 * @return pointer to the point.
 */
struct KM_Point* Point(double x, double y);

/**
 * Destroy a point.
 *
 * @param point point to be destroyed.
 */
void Free_Point(struct KM_Point *point);

/**
 * Calculate the distance from two points.
 *
 * @param p1 origin point
 * @param p2 destination point
 * @return distance from p1 to p2
 */
double KM_Point_GetDistance(struct KM_Point *p1, struct KM_Point *p2);

#endif