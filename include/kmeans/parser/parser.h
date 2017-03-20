#ifndef KMEANS_PARSER_PARSER_H
#define KMEANS_PARSER_PARSER_H

#include <kmeans/geometry/point.h>
#include <kmeans/parser/reader.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Parse a data file and return an array of points out of it.
 *
 * @param file file to be parsed.
 * @param output array that will be used as output of the parser.
 */
void KM_Parser_Parse(struct KM_FileReader *file, struct KM_Point **output);

struct KM_Point* GetPointFromString(char *string);

#ifdef __cplusplus
}
#endif



#endif