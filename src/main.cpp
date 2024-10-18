#include <stdio.h>

#include "mdi.h"
#include "node_library.h"


int main( int argc, char *argv[] )
{
    MDI mdi;

    if( MDI_Init( &mdi ) != MDI_STATE_INIT_OK )
    {
        return 1;
    }

    NodeLibrary nodeLib;
    if( !NodeLibrary_Init( &nodeLib ) )
    {
        printf("Error, unable to init NodeLibrary!\n");
    }

    if( !NodeLibrary_AddDirectory( &nodeLib, "TestDir 1" ) )
    {
        printf("Error, failed to add directory 1!\n");
    }
    if( !NodeLibrary_AddDirectory( &nodeLib, "TestDir 2" ) )
    {
        printf("Error, failed to add directory 2!\n");
    }
    if( !NodeLibrary_AddDirectory( &nodeLib, "TestDir 3" ) )
    {
        printf("Error, failed to add directory 3!\n");
    }


    if( !NodeLibrary_AddNode( &nodeLib, "Node 1", "TestDir 2" ) )
    {
        printf("Error, failed to add node 1!\n");
    }
    if( !NodeLibrary_AddNode( &nodeLib, "Node 2", "TestDir 2" ) )
    {
        printf("Error, failed to add node 2!\n");
    }
    if( !NodeLibrary_AddNode( &nodeLib, "Node 3", "TestDir 2" ) )
    {
        printf("Error, failed to add node 3!\n");
    }
    if( !NodeLibrary_AddNode( &nodeLib, "Node 4", "TestDir 1" ) )
    {
        printf("Error, failed to add node 4!\n");
    }

    NodeLibrary_Deinit( &nodeLib );


    MDI_Show( &mdi );
    MDI_Deinit( &mdi );

    return 0;
}