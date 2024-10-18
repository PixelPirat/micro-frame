#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "node_library.h"


const size_t DirecoryStartSize = 10;
const size_t NodeEntryStartSize = 50;


static bool nodeLibrary_GetDirectoryIndex( NodeLibrary *lib, const char *directory, size_t *index );
static size_t nodeLibrary_GetNodeCount( NodeLibrary *lib, size_t directoryIndex );


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

    void* nodes = calloc( NodeEntryStartSize, sizeof( NodeEntry ) );
    if( nodes == NULL )
    {
        return false;
    }
    lib->nodeCapasity = NodeEntryStartSize;
    lib->nodes = (NodeEntry *)nodes;

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

bool NodeLibrary_AddDirectory( NodeLibrary *lib, const char *name )
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

    return true;
}

bool NodeLibrary_AddNode( NodeLibrary *lib, const char *name, const char *directory )
{
    if( lib == NULL )
    {
        return false;
    }

    if( lib->nodeCapasity == lib->nodeElements )
    {
        // TODO: realloc to fit new data
        return false;
    }

    size_t directoryIndex = 0;
    if( !nodeLibrary_GetDirectoryIndex( lib, directory, &directoryIndex ) )
    {
        // The directory does not exist
        return false;
    }

    NodeEntry * node = lib->nodes + lib->nodeElements++;
    node->name = name;
    node->directoryIndex = directoryIndex;

    return true;
}


static bool nodeLibrary_GetDirectoryIndex( NodeLibrary *lib, const char *directory, size_t *index )
{
    if( lib == NULL )
    {
        return false;
    }

    if( lib->directoryElements == 0 )
    {
        return false;
    }

    bool directoryHit = false;
    for( size_t i = 0; i < lib->directoryElements; i++ )
    {
        if( strcmp( directory, lib->directories[ i ] ) == 0 )
        {
            *index = i;
            directoryHit = true;
            break;
        }
    }

    return directoryHit;
}

static size_t nodeLibrary_GetNodeCount( NodeLibrary *lib, size_t directoryIndex )
{
    if( lib == NULL )
    {
        return 0;
    }

    if( lib->directoryElements == 0 || directoryIndex >= lib->directoryElements )
    {
        return 0;
    }

    if( lib->nodeElements == 0 )
    {
        return 0;
    }

    size_t count = 0;
    NodeEntry * node;

    for( size_t i = 0; i < lib->nodeElements; i++ )
    {
        node = lib->nodes + i;
        if( node->directoryIndex == directoryIndex )
        {
            count++;
        }
    }

    return count;
}




void NodeLibrary_PrintDirectories( NodeLibrary *lib )
{
    if( lib == NULL )
    {
        printf( "Not NodeLibrary found!\n" );
    }

    printf( "Directories: %d\n", lib->directoryElements );
    printf( "Nodes: %d\n", lib->nodeElements );

    
    for( size_t i = 0; i < lib->directoryElements; i++ )
    {
        printf( "%s\n", lib->directories[ i ] );

        NodeEntry * node;
        for( size_t n = 0; n < lib->nodeElements; n++ )
        {
            node = lib->nodes + n;
            if( node->directoryIndex == i )
            {
                printf( "\t%s\n", node->name );
            }
        }
    }
}