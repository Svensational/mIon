#ifndef EVENT_H
#define EVENT_H

#include <algorithm>
#include <list>

namespace mion
{

template<typename... Types> class Event
{
    class Callback
    {
    public:
        virtual ~Callback() {};
        virtual void operator()( Types... p_args ) const = 0;
        virtual bool operator==( Callback const & p_other ) const = 0;
    };

    class Callback_Free : public Callback
    {
    public:
        explicit Callback_Free( void ( * p_pFunction )( Types... ) ) :
            Callback(), m_pFunction( p_pFunction )
        {
        }

        virtual ~Callback_Free() {};

        virtual void operator()( Types... p_args ) const
        {
            ( *m_pFunction )( p_args... );
        }

        virtual bool operator==( Callback const & p_other ) const
        {
            Callback_Free const * const pOther = dynamic_cast<Callback_Free const * const>( &p_other );
            if ( pOther )
            {
                return m_pFunction == pOther->m_pFunction;
            }
            else
            {
                return false;
            }
        }
    private:
        void ( * m_pFunction )( Types... );
    };

    template<typename T>
    class Callback_Member : public Callback
    {
    public:
        Callback_Member( T * p_pInstance, void ( T:: * p_pFunction )( Types... ) ) :
            Callback(), m_pInstance( p_pInstance ), m_pFunction( p_pFunction )
        {
        }

        virtual void operator()( Types... p_args ) const
        {
            ( m_pInstance->*m_pFunction )( p_args... );
        }

        virtual bool operator==( Callback const & p_other ) const
        {
            Callback_Member<T> const * const pOther = dynamic_cast<Callback_Member<T> const * const>( &p_other );
            if ( pOther )
            {
                return m_pInstance == pOther->m_pInstance && m_pFunction == pOther->m_pFunction;
            }
            else
            {
                return false;
            }
        }
    private:
        T * m_pInstance;
        void ( T:: * m_pFunction )( Types... );
    };

public:
    Event() {}

    virtual ~Event()
    {
        // delete the callbacks
        for ( Callback const * pCallback : m_aCallbacks )
        {
            delete pCallback;
        }
    }

    void trigger( Types... p_args ) const
    {
        // invoke all callbacks
        for ( Callback const * const pCallback : m_aCallbacks )
        {
            ( *pCallback )( p_args... );
        }
    }

    void add( void ( * p_pFunction )( Types... ) )
    {
        if ( p_pFunction )
        {
            add( new Callback_Free( p_pFunction ) );
        }
    }

    template<typename T>
    void add( T * p_pInstance, void ( T:: * p_pFunction )( Types... ) )
    {
        if ( p_pInstance && p_pFunction )
        {
            add( new Callback_Member<T>( p_pInstance, p_pFunction ) );
        }
    }

    void remove( void ( * p_pFunction )( Types... ) )
    {
        if ( p_pFunction )
        {
            remove( new Callback_Free( p_pFunction ) );
        }
    }

    template<typename T>
    void remove( T * p_pInstance, void ( T:: * p_pFunction )( Types... ) )
    {
        if ( p_pInstance && p_pFunction )
        {
            remove( new Callback_Member<T>( p_pInstance, p_pFunction ) );
        }
    }

    operator bool() const
    {
        return !m_aCallbacks.empty();
    }

private:
    std::list<Callback const *> m_aCallbacks;

    void add( Callback const * const p_pCallback )
    {
        const int n = count_if( m_aCallbacks.cbegin(), m_aCallbacks.cend(), [&]( Callback const * const p_pOther ) -> bool
        {
            return *p_pCallback == *p_pOther;
        } );
        if ( n == 0 )
        {
            m_aCallbacks.push_back( p_pCallback );
        }
    }

    void remove( Callback const * const p_pCallback )
    {
        m_aCallbacks.remove_if( [&]( Callback const * const p_pOther ) -> bool
        {
            return *p_pCallback == *p_pOther;
        } );
    }
};

} // namespace mion

#endif // EVENT_H
