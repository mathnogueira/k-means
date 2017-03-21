#include <kmeans/geometry/point.h>
#include <stdlib.h>
#include <math.h>

/**
* Create a new point.
*
* @param dimensions number of dimensions of the point.
* @param input coordinates used as input of the new point.
* @return pointer to the point.
*/
struct KM_Point* KM_Point_Create(unsigned int dimensions, void *input)
{
	unsigned int i = 0;
	struct KM_Point* point = (struct KM_Point*) malloc(sizeof(struct KM_Point));
	point->dimensions = dimensions;
	point->coord = (double*) malloc(sizeof(double) * dimensions);
	if (input != NULL) {
		double *coordinates = (double*) input;
		for (; i < dimensions; ++i) {
			point->coord[i] = coordinates[i];
		}
	} else {
		for (; i < dimensions; ++i)
			point->coord[0] = 0;
	}
	return point;
}

/**
 * Destroy a point.
 *
 * @param point point to be destroyed.
 */
void KM_Point_Destroy(struct KM_Point *point)
{
	if (point != NULL) 
		free(point->coord);
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
	double sum = 0;
	unsigned int i = 0;
	for (; i < p1->dimensions; ++i) {
		sum += pow(p1->coord[i] - p2->coord[i], 2);
	}
	return sqrt(sum);
}

/**
* Clone a new point using the values of other point.
*
* @param point point to be cloned.
* @return pointer to the new point.
*/
struct KM_Point* KM_Point_Clone(struct KM_Point *point)
{
	return KM_Point_Create(point->dimensions, point->coord);
}

/**
* Check if two points are equal.
*
* @param point1 first point to be compared.
* @param point2 second point to be compared.
* @return true if both are equal, false otherwise.
*/
bool KM_Point_Equals(struct KM_Point *point1, struct KM_Point *point2)
{
	bool equal = true;
	unsigned int i = 0;
	equal &= point1->dimensions == point2->dimensions;
	/*while (equal && i < point1->dimensions) {
		equal &= point1->coord[i] == point2->coord[i];
		i++;
	}*/
	equal &= (KM_Point_GetDistance(point1, point2) < 0.0001);
	return equal;
}


void KM_Point_Print(struct KM_Point *point)
{
	unsigned int d = 0;
	printf("P(");
	for (; d < point->dimensions-1; ++d) {
		printf("%.2f, ", point->coord[d]);
	}
	printf("%.2f", point->coord[d]);
	printf(") --> %.0f\n", point->classification);
}