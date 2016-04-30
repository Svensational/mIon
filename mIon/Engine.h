#ifndef ENGINE_H
#define ENGINE_H

#define engine mion::Engine::getInstance()

namespace mion
{

class Window;

class Engine
{
public:
    Engine();
    virtual ~Engine();
    virtual int run() = 0;

    static Engine * const getInstance();

protected:
    static Engine * s_pInstance;

    bool m_bRunning;
    Window * m_pWindow;

    void renderLoop();
    void logicLoop();
};

} // namespace mion

#endif // ENGINE_H
