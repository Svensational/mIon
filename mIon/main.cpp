#include "platform/Engine_Win.h"

int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int nCmdShow )
{
    mion::Engine_Win engine( hInstance );

    return engine.run();
}
