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
    struct KM_List *output = KM_List_Create();
    KM_Parser_Parse(reader, output);
    ASSERT_EQ(output->size, 149);
    struct KM_Point *p = (struct KM_Point*) KM_List_Get(output, 0);
    ASSERT_DOUBLE_EQ(p->coord[0], 5.1);
    free(output);
}