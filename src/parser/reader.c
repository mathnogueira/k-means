#include <kmeans/parser/reader.h>
#include <stdlib.h>

/**
 * Open a text file in read mode and get all its information.
 *
 * @param filename name of the file to open.
 * @return pointer to the FileReader structure.
 */
struct KM_FileReader* KM_FileReader_Open(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return NULL;
    struct KM_FileReader *reader = (struct KM_FileReader*) malloc(sizeof(struct KM_FileReader));
    reader->filename = filename;
    reader->file = fopen(filename, "r");
    fseek(file, 0L, SEEK_END);
    reader->size = ftell(file);
    rewind(file);
    reader->bufferPointer = 0;
    reader->readPointer = 0;
    reader->buffer = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    return reader;
}

/**
 * Read a line from the file.
 *
 * @param line pointer to an array that will be populated with the line.
 * @param file file that will be read.
 * @return true if a file is read, false if got to the end of the file.
 */
bool KM_FileReader_ReadLine(char *line, struct KM_FileReader *file)
{
    char character;
    unsigned long lineCounter = 0;
    /* It is comparing 1 more char to find the '\0' char. */
    while (file->readPointer <= file->size) {
        if (file->bufferPointer == 0) {
            fread(file->buffer, sizeof(char), BUFFER_SIZE, file->file);
        }
        character = file->buffer[file->bufferPointer];
        file->bufferPointer = (file->bufferPointer + 1) % BUFFER_SIZE;
        ++file->readPointer;
        if (character == '\n' || character == '\0') {
            line[lineCounter] = '\0';
            return true;
        }
        line[lineCounter++] = character;
    }

    return false;
}

/**
 * Close the file.
 *
 * @param file file that got opened using the KM_FileReader_Open function.
 */
void KM_FileReader_Close(struct KM_FileReader *file)
{
    if (file != NULL) {
        if (file->file != NULL)
            fclose(file->file);
        if (file->buffer != NULL)
            free(file->buffer);
        free(file);
    } 
}