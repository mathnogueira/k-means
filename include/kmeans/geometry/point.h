#ifndef KMEANS_GEOMETRY_POINT_H
#define KMEANS_GEOMETRY_POINT_H

#include <kmeans/types.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* Struct that represents a point in the algorithm.
	*/
	struct KM_Point {
		double *coord;
		unsigned int dimensions;
		double classification;
	};

	/**
	* Create a new point.
	*
	* @param dimensions number of dimensions of the point.
	* @param input coordinates used as input of the new point.
	* @return pointer to the point.
	*/
	struct KM_Point* KM_Point_Create(unsigned int dimensions, void *input);

	/**
	* Destroy a point.
	*
	* @param point point to be destroyed.
	*/
	void KM_Point_Destroy(struct KM_Point *point);

	/**
	* Calculate the distance from two points.
	*
	* @param p1 origin point
	* @param p2 destination point
	* @return distance from p1 to p2
	*/
	double KM_Point_GetDistance(struct KM_Point *p1, struct KM_Point *p2);

	/**
	 * Clone a new point using the values of other point.
	 *
	 * @param point point to be cloned.
	 * @return pointer to the new point.
	 */
	struct KM_Point* KM_Point_Clone(struct KM_Point *point);

	/**
	 * Check if two points are equal.
	 *
	 * @param point1 first point to be compared.
	 * @param point2 second point to be compared.
	 * @return true if both are equal, false otherwise.
	 */
	bool KM_Point_Equals(struct KM_Point *point1, struct KM_Point *point2);

	void KM_Point_Print(struct KM_Point *point);

#ifdef __cplusplus
}
#endif

#endif