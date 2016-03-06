#ifndef VEC2_H
#define VEC2_H

#include <array>
#include <ostream>
#include "Point.forward.h"

namespace mion
{

namespace math
{

template <typename T>
class Size2
{
public:
    // c'tors
    Size2() :
        m_aElements {T( 0 ), T( 0 )}
    {}

    Size2( T p_width, T p_height ) :
        m_aElements {p_width, p_height}
    {}

    Size2( Size2<T> const & p_sizeOther ) :
        m_aElements {p_sizeOther.m_aElements}
    {}

    Size2( Size2<T> && p_sizeOther )
    {
        std::swap( m_aElements, p_sizeOther.m_aElements );
    }

    template <typename S>
    explicit Size2( Size2<S> const & p_sizeOther ) :
        m_aElements {T( p_sizeOther[0] ), T( p_sizeOther[1] )}
    {}

    explicit Size2( Vec2<T> const & p_vec ) :
        m_aElements {p_vec[0], p_vec[1]}
    {}

    Size2( Point2<T> const & p_pointA, Point2<T> const & p_pointB ) :
        m_aElements {T( std::abs( p_pointB[0] - p_pointA[0] ) ), T( std::abs( p_pointB[1] - p_pointA[1] ) )}
    {}

    // Assignment operators
    Size2<T> & operator=( Size2<T> const & p_sizeOther )
    {
        m_aElements = p_sizeOther.m_aElements;
        return *this;
    }

    Size2<T> & operator=( Size2<T> && p_sizeOther )
    {
        std::swap( m_aElements, p_sizeOther.m_aElements );
        return *this;
    }

    // Access
    T & operator[]( size_t i )
    {
        return m_aElements[i];
    }

    T operator[]( size_t i ) const
    {
        return m_aElements[i];
    }

    T width() const
    {
        return m_aElements[0];
    }

    T height() const
    {
        return m_aElements[1];
    }

    void width( T p_width )
    {
        m_aElements[0] = p_width;
    }

    void height( T p_height )
    {
        m_aElements[1] = p_height;
    }

    T * data()
    {
        return m_aElements.data();
    }

    T const * data() const
    {
        return m_aElements.data();
    }

    // casting
    Vec2<T> to_Vec() const
    {
        return Vec2<T>( *this );
    }

    // comparison operators
    bool operator==( Size2<T> const & p_sizeOther ) const
    {
        return m_aElements == p_sizeOther.m_aElements;
    }

    bool operator!=( Size2<T> const & p_sizeOther ) const
    {
        return m_aElements != p_sizeOther.m_aElements;
    }

    // other functions
    real aspectratio() const
    {
        return m_aElements[0] / real( m_aElements[1] );
    }

private:
    std::array<T, 2> m_aElements;
};



template <typename T>
std::ostream & operator<< ( std::ostream & p_ostream, Size2<T> const & p_size )
{
    p_ostream << p_vec.x() << "x" << p_vec.y();
    return p_ostream;
}

} // namespace math

} // namespace mion

#endif // VEC2_H
