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