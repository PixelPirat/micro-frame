#ifndef __NODE_LIBRARY_H__
#define __NODE_LIBRARY_H__


#include <stddef.h>
#include <stdbool.h>


typedef struct {
    const char * name;
    size_t directoryElement;
} NodeEntry;

typedef struct {
    const char ** directories;
    size_t directoryElements;
    size_t directoryCapasity;

    NodeEntry ** nodes;
    size_t nodeElements;
    size_t nodeCapasity;
} NodeLibrary;


bool NodeLibrary_Init( NodeLibrary *lib );
bool NodeLibrary_Deinit( NodeLibrary *lib );

bool NodeLibrary_AddDirectory( NodeLibrary *lib, const char* name );
bool NodeLibrary_AddNode( NodeLibrary *lib, const char* name, const char * directory );


#endif//__NODE_LIBRARY_H__