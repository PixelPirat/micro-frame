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
        printf("Error, failed to add a directory!\n");
    }

    NodeLibrary_Deinit( &nodeLib );


    MDI_Show( &mdi );
    MDI_Deinit( &mdi );

    return 0;
}