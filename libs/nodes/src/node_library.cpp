#include <stdlib.h>

#include "node_library.h"


const size_t DirecoryStartSize = 10;
const size_t NodeEntryStartSize = 50;


bool NodeLibrary_Init( NodeLibrary *lib )
{
    if( lib == NULL )
    {
        return false;
    }


    lib->directoryCapasity = 0;
    lib->directoryElements = 0;

    void* directory = calloc( DirecoryStartSize, sizeof( const char * ) );
    if( directory == NULL )
    {
        return false;
    }
    lib->directoryCapasity = DirecoryStartSize;
    lib->directories = (const char **)directory;


    lib->nodeCapasity = 0;
    lib->nodeElements = 0;

    void* nodes = calloc( NodeEntryStartSize, sizeof( NodeEntry * ) );
    if( nodes == NULL )
    {
        return false;
    }
    lib->nodeCapasity = NodeEntryStartSize;
    lib->nodes = (NodeEntry **)nodes;

    return true;
}

bool NodeLibrary_Deinit( NodeLibrary *lib )
{
    if( lib == NULL )
    {
        return false;
    }

    if( lib->directories != NULL )
    {
        free( lib->directories );
    }

    if( lib->nodes != NULL )
    {
        free( lib->nodes );
    }

    return true;
}

bool NodeLibrary_AddDirectory( NodeLibrary *lib, const char* name )
{
    if( lib == NULL )
    {
        return false;
    }

    if( lib->directoryCapasity == lib->directoryElements )
    {
        // TODO: realloc to fit new data
        return false;
    }

    lib->directories[ lib->directoryElements++ ] = name;

    return false;
}

bool NodeLibrary_AddNode( NodeLibrary *lib, const char* name, const char * directory )
{
    return false;
}