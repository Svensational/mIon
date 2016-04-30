#ifndef ENGINE_WIN_H
#define ENGINE_WIN_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Engine.h"

namespace mion
{

class Engine_Win : public Engine
{
public:
    virtual ~Engine_Win();
    virtual int run();
    virtual void quit();

    static void init( HINSTANCE p_hInstance );

private:
    HINSTANCE m_hInstance;

    bool registerWindowClass() const;
    bool unregisterWindowClass() const;

    explicit Engine_Win( HINSTANCE p_hInstance );
    static LRESULT CALLBACK WndProc( HWND p_hWnd, UINT p_uiMessage, WPARAM p_wParam, LPARAM p_lParam );
};

} // namespace mion

#endif // ENGINE_WIN_H
