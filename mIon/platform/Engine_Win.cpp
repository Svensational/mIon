#include "Engine_Win.h"
#include <thread>
#include "Window_Win.h"

#include <iostream>

namespace mion
{

Engine_Win::Engine_Win( HINSTANCE p_hInstance ) :
    Engine(),
    m_hInstance( p_hInstance )
{
    registerWindowClass();
    m_pWindow = new Window_Win( m_hInstance );
    m_pWindow->m_eventDestroyed.add( this, &Engine_Win::quit );
}

Engine_Win::~Engine_Win()
{
    delete m_pWindow;
    unregisterWindowClass();
}

int Engine_Win::run()
{
    m_bRunning = true;
    std::thread threadRenderLoop( &Engine_Win::renderLoop, this );
    std::thread threadLogicLoop( &Engine_Win::logicLoop, this );

    // message loop
    BOOL bRet;
    MSG msg;
    while ( ( bRet = GetMessageW( &msg, nullptr, 0, 0 ) ) != 0 )
    {
        if ( bRet == -1 )
        {
            //Dafuq? I quit!
            quit();
        }
        else
        {
            TranslateMessage( &msg );
            DispatchMessageW( &msg );
        }
        std::this_thread::sleep_for( std::chrono::milliseconds( 4 ) );
    }

    m_bRunning = false;
    threadRenderLoop.join();
    threadLogicLoop.join();

    return 0;
}

void Engine_Win::quit()
{
    PostQuitMessage( 0 );
}

void Engine_Win::init( HINSTANCE p_hInstance )
{
    s_pInstance = new Engine_Win( p_hInstance );
}

bool Engine_Win::registerWindowClass() const
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &Engine_Win::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof( void * );
    wcex.hInstance = m_hInstance;
    wcex.hIcon = LoadIconW( NULL, IDI_APPLICATION );
    wcex.hCursor = LoadCursorW( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_BACKGROUND );
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"mIonEngine";
    wcex.hIconSm = wcex.hIcon;

    return RegisterClassExW( &wcex );
}

bool Engine_Win::unregisterWindowClass() const
{
    return UnregisterClassW( L"mIonEngine", m_hInstance );
}

LRESULT CALLBACK Engine_Win::WndProc( HWND p_hWnd, UINT p_uiMessage, WPARAM p_wParam, LPARAM p_lParam )
{
    Window_Win * const pWindow = reinterpret_cast<Window_Win *>( GetWindowLongPtrW( p_hWnd, 0 ) );
    if ( pWindow )
    {
        return pWindow->processMessage( p_uiMessage, p_wParam, p_lParam );
    }
    else
    {
        return DefWindowProcW( p_hWnd, p_uiMessage, p_wParam, p_lParam );
    }
}

} // namespace mion
