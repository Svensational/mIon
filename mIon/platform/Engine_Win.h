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
    explicit Engine_Win( HINSTANCE hInstance );
    virtual ~Engine_Win();
    virtual int run();

private:
    HINSTANCE m_hInstance;

    bool registerWindowClass() const;
    bool unregisterWindowClass() const;

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
};

} // namespace mion

#endif // ENGINE_WIN_H
