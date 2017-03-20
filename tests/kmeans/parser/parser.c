#include <gtest/gtest.h>
#include <kmeans/parser/parser.h>
#include <kmeans/parser/reader.h>
#include <kmeans/collections/list.h>
#include <kmeans/geometry/point.h>

TEST(Parser, GetPointFromString)
{
    char *str = strdup("0.11,0.3,52.1,2");
    struct KM_Point *point = GetPointFromString(str);
    ASSERT_DOUBLE_EQ(point->coord[0], 0.11);
}

TEST(Parser, ParseIrisFile)
{
    struct KM_FileReader *reader = KM_FileReader_Open("bin/files/iris.data");
    ASSERT_FALSE(reader == NULL);
    struct KM_Point *output = NULL;
    unsigned long points = 0;
    KM_Parser_Parse(reader, &output, &points);
    ASSERT_EQ(points, 149);
    ASSERT_DOUBLE_EQ(output[0].coord[0], 5.1);
    free(output);
    // KM_FileReader_Close(reader);
}