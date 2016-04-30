#include "Window_Win.h"
#include <windowsx.h>
#include "types.h"
#include "math/Point.h"

#include <iostream>
void testKey( mion::uint32 code )
{
    std::wcout << "Key: " << code << std::endl;
}
void testChar( mion::uint32 code )
{
    // WideCharToMultiByte !!!
    std::wcout << "Char: " << wchar_t( code ) << std::endl;
}

namespace mion
{

Window_Win::Window_Win( HINSTANCE p_hInstance ) :
    m_hWindow( nullptr )
{
    create( p_hInstance );

    m_eventKeyDown.add( testKey );
    m_eventCharInput.add( testChar );
}

Window_Win::~Window_Win()
{
    destroy();
}

LRESULT Window_Win::processMessage( UINT p_uiMessage, WPARAM p_wParam, LPARAM p_lParam )
{
    switch ( p_uiMessage )
    {
    case WM_PAINT:
        break;

        //mouse: https://msdn.microsoft.com/en-us/library/windows/desktop/ff468877%28v=vs.85%29.aspx
    case WM_MOUSEMOVE:
        if ( m_eventMouseMove )
        {
            m_eventMouseMove.trigger( math::Point2i( GET_X_LPARAM( p_lParam ),
                                                     GET_Y_LPARAM( p_lParam ) ),
                                      ( p_wParam & MK_CONTROL ) == MK_CONTROL,
                                      ( p_wParam & MK_SHIFT ) == MK_SHIFT );
        }
        break;

    case WM_LBUTTONDOWN:
        if ( m_eventMouseButtonLeftDown )
        {
            m_eventMouseButtonLeftDown.trigger( math::Point2i( GET_X_LPARAM( p_lParam ),
                                                               GET_Y_LPARAM( p_lParam ) ),
                                                ( p_wParam & MK_CONTROL ) == MK_CONTROL,
                                                ( p_wParam & MK_SHIFT ) == MK_SHIFT );
        }
        break;
    case WM_LBUTTONUP:
        if ( m_eventMouseButtonLeftUp )
        {
            m_eventMouseButtonLeftUp.trigger( math::Point2i( GET_X_LPARAM( p_lParam ),
                                                             GET_Y_LPARAM( p_lParam ) ),
                                              ( p_wParam & MK_CONTROL ) == MK_CONTROL,
                                              ( p_wParam & MK_SHIFT ) == MK_SHIFT );
        }
        break;
    case WM_RBUTTONDOWN:
        if ( m_eventMouseButtonRightDown )
        {
            m_eventMouseButtonRightDown.trigger( math::Point2i( GET_X_LPARAM( p_lParam ),
                                                                GET_Y_LPARAM( p_lParam ) ),
                                                 ( p_wParam & MK_CONTROL ) == MK_CONTROL,
                                                 ( p_wParam & MK_SHIFT ) == MK_SHIFT );
        }
        break;
    case WM_RBUTTONUP:
        if ( m_eventMouseButtonRightUp )
        {
            m_eventMouseButtonRightUp.trigger( math::Point2i( GET_X_LPARAM( p_lParam ),
                                                              GET_Y_LPARAM( p_lParam ) ),
                                               ( p_wParam & MK_CONTROL ) == MK_CONTROL,
                                               ( p_wParam & MK_SHIFT ) == MK_SHIFT );
        }
        break;
    case WM_MBUTTONDOWN:
        if ( m_eventMouseButtonMiddleDown )
        {
            m_eventMouseButtonMiddleDown.trigger( math::Point2i( GET_X_LPARAM( p_lParam ),
                                                                 GET_Y_LPARAM( p_lParam ) ),
                                                  ( p_wParam & MK_CONTROL ) == MK_CONTROL,
                                                  ( p_wParam & MK_SHIFT ) == MK_SHIFT );
        }
        break;
    case WM_MBUTTONUP:
        if ( m_eventMouseButtonMiddleUp )
        {
            m_eventMouseButtonMiddleUp.trigger( math::Point2i( GET_X_LPARAM( p_lParam ),
                                                               GET_Y_LPARAM( p_lParam ) ),
                                                ( p_wParam & MK_CONTROL ) == MK_CONTROL,
                                                ( p_wParam & MK_SHIFT ) == MK_SHIFT );
        }
        break;
    case WM_XBUTTONDOWN:
        if ( m_eventMouseButtonX1Down && ( GET_XBUTTON_WPARAM( p_wParam ) & XBUTTON1 ) == XBUTTON1 )
        {
            m_eventMouseButtonX1Down.trigger( math::Point2i( GET_X_LPARAM( p_lParam ), GET_Y_LPARAM( p_lParam ) ),
                                              ( GET_KEYSTATE_WPARAM( p_wParam ) & MK_CONTROL ) == MK_CONTROL,
                                              ( GET_KEYSTATE_WPARAM( p_wParam ) & MK_SHIFT ) == MK_SHIFT );
        }
        else if ( m_eventMouseButtonX2Down && ( GET_XBUTTON_WPARAM( p_wParam ) & XBUTTON2 ) == XBUTTON2 )
        {
            m_eventMouseButtonX2Down.trigger( math::Point2i( GET_X_LPARAM( p_lParam ), GET_Y_LPARAM( p_lParam ) ),
                                              ( GET_KEYSTATE_WPARAM( p_wParam ) & MK_CONTROL ) == MK_CONTROL,
                                              ( GET_KEYSTATE_WPARAM( p_wParam ) & MK_SHIFT ) == MK_SHIFT );
        }
        break;
    case WM_XBUTTONUP:
        if ( m_eventMouseButtonX1Up && ( GET_XBUTTON_WPARAM( p_wParam ) & XBUTTON1 ) == XBUTTON1 )
        {
            m_eventMouseButtonX1Up.trigger( math::Point2i( GET_X_LPARAM( p_lParam ), GET_Y_LPARAM( p_lParam ) ),
                                            ( GET_KEYSTATE_WPARAM( p_wParam ) & MK_CONTROL ) == MK_CONTROL,
                                            ( GET_KEYSTATE_WPARAM( p_wParam ) & MK_SHIFT ) == MK_SHIFT );
        }
        else if ( m_eventMouseButtonX2Up && ( GET_XBUTTON_WPARAM( p_wParam ) & XBUTTON2 ) == XBUTTON2 )
        {
            m_eventMouseButtonX2Up.trigger( math::Point2i( GET_X_LPARAM( p_lParam ), GET_Y_LPARAM( p_lParam ) ),
                                            ( GET_KEYSTATE_WPARAM( p_wParam ) & MK_CONTROL ) == MK_CONTROL,
                                            ( GET_KEYSTATE_WPARAM( p_wParam ) & MK_SHIFT ) == MK_SHIFT );
        }
        break;

    case WM_MOUSEWHEEL:
        if ( m_eventMouseWheel )
        {
            m_eventMouseWheel.trigger( GET_WHEEL_DELTA_WPARAM( p_wParam ) / real( WHEEL_DELTA ) );
        }
        break;
        /*case WM_MOUSEHWHEEL:
            if ( m_eventMouseWheelH )
            {
                m_eventMouseWheelH.trigger( GET_WHEEL_DELTA_WPARAM( wParam ) / real( WHEEL_DELTA ) );
            }
            break;*/

        // keyboard: https://msdn.microsoft.com/en-us/library/windows/desktop/ff468861%28v=vs.85%29.aspx
    case WM_KEYDOWN:
        if ( m_eventKeyDown )
        {
            m_eventKeyDown.trigger( p_wParam );
        }
        break;
    case WM_CHAR:
        if ( m_eventCharInput )
        {
            m_eventCharInput.trigger( p_wParam );
        }
        break;

    case WM_DESTROY:
        m_hWindow = nullptr;
        m_eventDestroyed.trigger();
        break;
    default:
        return DefWindowProcW( m_hWindow, p_uiMessage, p_wParam, p_lParam );
    }
    return 0;
}

bool Window_Win::create( HINSTANCE p_hInstance )
{
    m_hWindow = CreateWindowW( L"mIonEngine",
                               L"mIon engine example",
                               WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT,
                               CW_USEDEFAULT,
                               400,
                               300,
                               nullptr,
                               nullptr,
                               p_hInstance,
                               nullptr );

    if ( m_hWindow )
    {
        SetWindowLongPtrW( m_hWindow, 0, ( LONG_PTR ) this );

        ShowWindow( m_hWindow, SW_SHOW );
        UpdateWindow( m_hWindow );
    }

    return m_hWindow;
}

bool Window_Win::destroy()
{
    return DestroyWindow( m_hWindow );
}

} // namespace mion
