#include <gtest/gtest.h>
#include <kmeans/parser/reader.h>

TEST(FileReader, ReadLineByLine)
{
    bool readFile;
    struct KM_FileReader *file = KM_FileReader_Open("bin/files/file1.dat");
    if (file == NULL)
        FAIL();
    char line[100];
    
    readFile = KM_FileReader_ReadLine(line, file);
    ASSERT_TRUE(readFile);
    ASSERT_STREQ(line, "This is a random line");
    readFile = KM_FileReader_ReadLine(line, file);
    ASSERT_TRUE(readFile);
    ASSERT_STREQ(line, "This is another");
    readFile = KM_FileReader_ReadLine(line, file);
    ASSERT_TRUE(readFile);
    ASSERT_STREQ(line, "And this is the last one.");
    readFile = KM_FileReader_ReadLine(line, file);
    ASSERT_FALSE(readFile);
    KM_FileReader_Close(file);
}