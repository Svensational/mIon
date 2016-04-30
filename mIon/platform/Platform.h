#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef MION_PLATFORM_WIN

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Engine_Win.h"
#define MION_MAIN int fake_main(); \
    int WINAPI WinMain( HINSTANCE hInstance, \
                        HINSTANCE hPrevInstance, \
                        LPSTR lpCmdLine, \
                        int nCmdShow ) \
    { \
        mion::Engine_Win::init( hInstance ); \
        return fake_main(); \
    } \
    int fake_main() \

#endif // MION_PLATFORM_WIN

#endif // PLATFORM_H
