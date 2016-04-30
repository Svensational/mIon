#ifndef WINDOWAPP_WIN_H
#define WINDOWAPP_WIN_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Window.h"

namespace mion
{

class Window_Win : public Window
{

public:
    explicit Window_Win( HINSTANCE p_hInstance );
    virtual ~Window_Win();
    LRESULT processMessage( UINT p_uiMessage, WPARAM p_wParam, LPARAM p_lParam );

private:
    HWND m_hWindow;

    bool create( HINSTANCE p_hInstance );
    bool destroy();
};

} // namespace mion

#endif // WINDOWAPP_WIN_H
