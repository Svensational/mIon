#ifndef WINDOW_H
#define WINDOW_H

#include "Event.h"
#include "math/Point.forward.h"

namespace mion
{

class Window
{
public:
    Window();
    virtual ~Window();

    Event<math::Point2i, bool, bool> m_eventMouseMove;
    Event<math::Point2i, bool, bool> m_eventMouseButtonLeftDown;
    Event<math::Point2i, bool, bool> m_eventMouseButtonLeftUp;
    Event<math::Point2i, bool, bool> m_eventMouseButtonRightDown;
    Event<math::Point2i, bool, bool> m_eventMouseButtonRightUp;
    Event<math::Point2i, bool, bool> m_eventMouseButtonMiddleDown;
    Event<math::Point2i, bool, bool> m_eventMouseButtonMiddleUp;
    Event<math::Point2i, bool, bool> m_eventMouseButtonX1Down;
    Event<math::Point2i, bool, bool> m_eventMouseButtonX1Up;
    Event<math::Point2i, bool, bool> m_eventMouseButtonX2Down;
    Event<math::Point2i, bool, bool> m_eventMouseButtonX2Up;
    Event<real> m_eventMouseWheel;
    Event<real> m_eventMouseWheelH;

    Event<uint32> m_eventKeyDown;
    Event<uint32> m_eventCharInput;

    Event<> m_eventDestroyed;
};

} // namespace mion

#endif // WINDOW_H
