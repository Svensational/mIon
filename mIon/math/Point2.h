#ifndef POINT2_H
#define POINT2_H

#include <array>
#include <ostream>
#include "Vec.h"

namespace mion
{

namespace math
{

template <typename T>
class Point2
{
public:
    // c'tors
    Point2() :
        m_aElements {T( 0 ), T( 0 )}
    {}

    Point2( T p_x, T p_y ) :
        m_aElements {p_x, p_y}
    {}

    Point2( Point2<T> const & p_pointOther ) :
        m_aElements {p_pointOther.m_aElements}
    {}

    Point2( Point2<T> && p_pointOther )
    {
        std::swap( m_aElements, p_pointOther.m_aElements );
    }

    template <typename S>
    explicit Point2( Point2<S> const & p_pointOther ) :
        m_aElements {T( p_pointOther.x() ), T( p_pointOther.y() )}
    {}

    explicit Point2( Vec2<T> const & p_vec ) :
        m_aElements { p_vec[0], p_vec[1] }
    {}

    // Assignment operators
    Point2<T> & operator=( Point2<T> const & p_pointOther )
    {
        m_aElements = p_pointOther.m_aElements;
        return *this;
    }

    Point2<T> & operator=( Point2<T> && p_pointOther )
    {
        std::swap( m_aElements, p_pointOther.m_aElements );
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

    T x() const
    {
        return m_aElements[0];
    }

    T y() const
    {
        return m_aElements[1];
    }

    Point2<T> xx() const
    {
        return Point2( m_aElements[0], m_aElements[0] );
    }

    Point2<T> xy() const
    {
        return Point2( m_aElements[0], m_aElements[1] );
    }

    Point2<T> yx() const
    {
        return Point2( m_aElements[1], m_aElements[0] );
    }

    Point2<T> yy() const
    {
        return Point2( m_aElements[1], m_aElements[1] );
    }

    void x( T p_x )
    {
        m_aElements[0] = p_x;
    }

    void y( T p_y )
    {
        m_aElements[1] = p_y;
    }

    void xy( T p_x, T p_y )
    {
        m_aElements[0] = p_x;
        m_aElements[1] = p_y;
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

    // Arithmetic and compound assignment operators
    Point2<T> operator+( Vec2<T> const & p_vec ) const
    {
        return Point2<T>( m_aElements[0] + p_vec[0],
                          m_aElements[1] + p_vec[1] );
    }

    Point2<T> & operator+=( Vec2<T> const & p_vec )
    {
        m_aElements[0] += p_vec[0];
        m_aElements[1] += p_vec[1];
        return *this;
    }

    Point2<T> operator-( Vec2<T> const & p_vec ) const
    {
        return Point2<T>( m_aElements[0] - p_vec[0],
                          m_aElements[1] - p_vec[1] );
    }

    Point2<T> & operator-=( Vec2<T> const & p_vec )
    {
        m_aElements[0] -= p_vec[0];
        m_aElements[1] -= p_vec[1];
        return *this;
    }

    // comparison operators
    bool operator==( Point2<T> const & p_pointOther ) const
    {
        return m_aElements == p_pointOther.m_aElements;
    }

    bool operator!=( Point2<T> const & p_pointOther ) const
    {
        return m_aElements != p_pointOther.m_aElements;
    }

    // other functions
    inline real distance( Point2<T> const & p_pointOther ) const
    {
        return Vec2<T>( *this, p_pointOther ).length();
    }

    Point2<T> lerp( Point2<T> const & p_pointOther, real p_rT = real( 0.5 ) ) const
    {
        const real rS = real( 1.0 ) - p_rT;
        return Point2<T>( p_rT * m_aElements[0] + rS * p_pointOther.m_aElements[0],
                          p_rT * m_aElements[1] + rS * p_pointOther.m_aElements[1] );

    }

private:
    std::array<T, 2> m_aElements;
};



template <typename T>
inline real distance( Point2<T> const & p_pointA, Point2<T> const & p_pointB )
{
    return Vec2<T>( p_pointA, p_pointB ).length();
}

template <typename T>
inline Point2<T> lerp( Point2<T> const & p_pointA, Point2<T> const & p_pointB, real p_rT = real( 0.5 ) )
{
    return p_pointA.lerp( p_pointB, p_rT );
}

template <typename T>
std::ostream & operator<< ( std::ostream & p_ostream, Point2<T> const & p_point )
{
    p_ostream << "(" << p_point.x() << "/" << p_point.y() << ")";
    return p_ostream;
}

} // namespace math

} // namespace mion

#endif // POINT2_H
