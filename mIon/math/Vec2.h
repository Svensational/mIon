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
class Vec2
{
public:
    // c'tors
    Vec2() :
        m_aElements {T( 0 ), T( 0 )}
    {}

    Vec2( T p_x, T p_y ) :
        m_aElements {p_x, p_y}
    {}

    Vec2( Vec2<T> const & p_vecOther ) :
        m_aElements {p_vecOther.m_aElements}
    {}

    Vec2( Vec2<T> && p_vecOther )
    {
        std::swap( m_aElements, p_vecOther.m_aElements );
    }

    template <typename S>
    explicit Vec2( Vec2<S> const & p_vecOther ) :
        m_aElements {T( p_vecOther.x() ), T( p_vecOther.y() )}
    {}

    explicit Vec2( Point2<T> const & p_point ) :
        m_aElements {p_point[0], p_point[1]}
    {}

    Vec2( Point2<T> const & p_pointA, Point2<T> const & p_pointB ) :
        m_aElements {p_pointB[0] - p_pointA[0], p_pointB[1] - p_pointA[1]}
    {}

    // Assignment operators
    Vec2<T> & operator=( Vec2<T> const & p_vecOther )
    {
        m_aElements = p_vecOther.m_aElements;
        return *this;
    }

    Vec2<T> & operator=( Vec2<T> && p_vecOther )
    {
        std::swap( m_aElements, p_vecOther.m_aElements );
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

    Vec2<T> xx() const
    {
        return Vec2( m_aElements[0], m_aElements[0] );
    }

    Vec2<T> xy() const
    {
        return Vec2( m_aElements[0], m_aElements[1] );
    }

    Vec2<T> yx() const
    {
        return Vec2( m_aElements[1], m_aElements[0] );
    }

    Vec2<T> yy() const
    {
        return Vec2( m_aElements[1], m_aElements[1] );
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
    Point2<T> to_Point() const
    {
        return Point2<T>( *this );
    }

    // Arithmetic and compound assignment operators
    Vec2<T> operator+( Vec2<T> const & p_vecOther ) const
    {
        return Vec2<T>( m_aElements[0] + p_vecOther.m_aElements[0],
                        m_aElements[1] + p_vecOther.m_aElements[1] );
    }

    Vec2<T> & operator+=( Vec2<T> const & p_vecOther )
    {
        m_aElements[0] += p_vecOther.m_aElements[0];
        m_aElements[1] += p_vecOther.m_aElements[1];
        return *this;
    }

    Vec2<T> operator-() const
    {
        return Vec2<T>( -m_aElements[0], -m_aElements[1] );
    }

    Vec2<T> operator-( Vec2<T> const & p_vecOther ) const
    {
        return Vec2<T>( m_aElements[0] - p_vecOther.m_aElements[0],
                        m_aElements[1] - p_vecOther.m_aElements[1] );
    }

    Vec2<T> & operator-=( Vec2<T> const & p_vecOther )
    {
        m_aElements[0] -= p_vecOther.m_aElements[0];
        m_aElements[1] -= p_vecOther.m_aElements[1];
        return *this;
    }

    Vec2<T> operator*( T p_a ) const
    {
        return Vec2<T>( m_aElements[0] * p_a,
                        m_aElements[1] * p_a );
    }

    Vec2<T> & operator*=( T p_a )
    {
        m_aElements[0] *= p_a;
        m_aElements[1] *= p_a;
        return *this;
    }

    Vec2<T> operator/( T p_a ) const
    {
        return Vec2<T>( m_aElements[0] / p_a,
                        m_aElements[1] / p_a );
    }

    Vec2<T> & operator/=( T p_a )
    {
        m_aElements[0] /= p_a;
        m_aElements[1] /= p_a;
        return *this;
    }

    // comparison operators
    bool operator==( Vec2<T> const & p_vecOther ) const
    {
        return m_aElements == p_vecOther.m_aElements;
    }

    bool operator!=( Vec2<T> const & p_vecOther ) const
    {
        return m_aElements != p_vecOther.m_aElements;
    }

    // other functions
    T dot( Vec2<T> const & p_vecOther ) const
    {
        return m_aElements[0] * p_vecOther.m_aElements[0] +
               m_aElements[1] * p_vecOther.m_aElements[1];
    }

    real length() const
    {
        return sqrt( dot( *this ) );
    }

    Vec2<T> & normalize()
    {
        return operator/=( length() );
    }

    Vec2<T> normalized() const
    {
        return operator/( length() );
    }

    Vec2<T> lerp( Vec2<T> const & p_vecOther, real p_rT = real( 0.5 ) ) const
    {
        const real rS = real( 1.0 ) - p_rT;
        return Vec2<T>( p_rT * m_aElements[0] + rS * p_vecOther.m_aElements[0],
                        p_rT * m_aElements[1] + rS * p_vecOther.m_aElements[1] );

    }

private:
    std::array<T, 2> m_aElements;
};



template <typename T>
inline Vec2<T> operator*( T p_a, Vec2<T> const & p_vec )
{
    return p_vec * p_a;
}

template <typename T>
inline T dot( Vec2<T> const & p_vecA, Vec2<T> const & p_vecB )
{
    return p_vecA.dot( p_vecB );
}

template <typename T>
inline Vec2<T> lerp( Vec2<T> const & p_vecA, Vec2<T> const & p_vecB, real p_rT = real( 0.5 ) )
{
    return p_vecA.lerp( p_vecB, p_rT );
}

template <typename T>
std::ostream & operator<< ( std::ostream & p_ostream, Vec2<T> const & p_vec )
{
    p_ostream << "(" << p_vec.x() << "/" << p_vec.y() << ")";
    return p_ostream;
}

} // namespace math

} // namespace mion

#endif // VEC2_H
