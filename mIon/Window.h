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

protected:
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
    Event<float> m_eventMouseWheel;
    Event<float> m_eventMouseWheelH;

    Event<unsigned int> m_eventCharInput;
};

} // namespace mion

#endif // WINDOW_H
