#ifndef ENGINE_H
#define ENGINE_H

namespace mion
{

class Window;

class Engine
{
public:
    Engine();
    virtual ~Engine();
    virtual int run() = 0;

protected:
    bool m_bRunning;
    Window * m_pWindow;

    void renderLoop();
    void logicLoop();
};

} // namespace mion

#endif // ENGINE_H
