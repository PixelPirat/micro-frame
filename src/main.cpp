#include "mdi.h"


int main( int argc, char *argv[] )
{
    MDI mdi;

    if( mdi_init( &mdi ) != MDI_STATE_INIT_OK )
    {
        return 1;
    }

    mdi_show( &mdi );
    mdi_deinit( &mdi );

    return 0;
}