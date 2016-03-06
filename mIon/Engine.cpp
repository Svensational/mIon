#include "Engine.h"
#include <thread>

namespace mion
{

Engine::Engine() :
    m_bRunning( false ),
    m_pWindow( nullptr )
{
}

Engine::~Engine()
{
}

void Engine::renderLoop()
{
    const std::chrono::high_resolution_clock::duration dur = std::chrono::nanoseconds( 1000000000 / 60 );
    std::chrono::high_resolution_clock::time_point tp;
    while ( m_bRunning )
    {
        tp = std::chrono::high_resolution_clock::now() + dur;

        // do stuff!

        std::this_thread::sleep_until( tp );
    }
}

void Engine::logicLoop()
{
    const std::chrono::high_resolution_clock::duration dur = std::chrono::nanoseconds( 1000000000 / ( 60 * 4 ) );
    std::chrono::high_resolution_clock::time_point tp;
    while ( m_bRunning )
    {
        tp = std::chrono::high_resolution_clock::now() + dur;

        // do stuff!

        std::this_thread::sleep_until( tp );
    }
}

} // namespace mion
