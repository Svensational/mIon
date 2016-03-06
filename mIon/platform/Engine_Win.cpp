#include "Engine_Win.h"
#include <thread>
#include "Window_Win.h"

namespace mion
{

Engine_Win::Engine_Win( HINSTANCE hInstance ) :
    Engine(),
    m_hInstance( hInstance )
{
    registerWindowClass();
    m_pWindow = new Window_Win( m_hInstance );
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
            PostQuitMessage( 0 );
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

LRESULT CALLBACK Engine_Win::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    Window_Win * pWindow = reinterpret_cast<Window_Win *>( GetWindowLongPtrW( hWnd, 0 ) );
    if ( pWindow )
    {
        return pWindow->processMessage( message, wParam, lParam );
    }
    else
    {
        return DefWindowProcW( hWnd, message, wParam, lParam );
    }
}

} // namespace mion
