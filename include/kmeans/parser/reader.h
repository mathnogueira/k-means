#ifndef KMEANS_PARSER_READER_H
#define KMEANS_PARSER_READER_H

#include <kmeans/types.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Size of the read buffer */
#define BUFFER_SIZE 4096

/**
 * Struture that stores all information needed to open and read a file from
 * the secondary storage device.
 *
 * @param Matheus Nogueira
 */
struct KM_FileReader {
    const char *filename;
    FILE *file;
    unsigned long size;
    unsigned long bufferPointer;
    unsigned long readPointer;
    char *buffer;
};

/**
 * Open a text file in read mode and get all its information.
 *
 * @param filename name of the file to open.
 * @return pointer to the FileReader structure.
 */
struct KM_FileReader* KM_FileReader_Open(const char *filename);

/**
 * Read a line from the file.
 *
 * @param line pointer to an array that will be populated with the line.
 * @param file file that will be read.
 * @return true if a file is read, false if got to the end of the file.
 */
bool KM_FileReader_ReadLine(char *line, struct KM_FileReader *file);

/**
 * Close the file.
 *
 * @param file file that got opened using the KM_FileReader_Open function.
 */
void KM_FileReader_Close(struct KM_FileReader *file);

#ifdef __cplusplus
}
#endif

#endif