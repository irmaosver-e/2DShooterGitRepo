#ifndef __Vector2D__
#define __Vector2D__

#include <math.h>

template <class T>
struct Vec2
{
	Vec2(T px = 0, T py = 0)
	{
		m_x = px;
		m_y = py;
	}

	T getX() const
	{
		return m_x;
	}

	T getY() const
	{
		return m_y;
	}

	T* getXPtr()
	{
		return &m_x;
	}

	T* getYPtr()
	{
		return &m_y;
	}

	T& getXRef()
	{
		return m_x;
	}

	T& getYRef()
	{
		return m_y;
	}

	T Lenght()
	{
		return sqrt(SquareLenght());
	}

	T SquareLenght()
	{
		return (m_x * m_x) + (m_y * m_y);
	}

	Vec2<T> operator*(T f) const
	{
		return Vec2(m_x * f, m_y * f);
	}

	Vec2<T> operator%(T f) const
	{
		return Vec2(m_x % f, m_y % f);
	}

	void operator +=(const Vec2<T>& v)
	{
		m_x += v.m_x ;
		m_y += v.m_y ;
	}

	void operator -=(const Vec2<T>& v)
	{
		m_x -= v.m_x ;
		m_y -= v.m_y ;
	}

	Vec2<T> operator + (const Vec2<T>& v)
	{
		return Vec2<T>(m_x + v.m_x , m_y + v.m_y );
	}

	Vec2<T> operator - (const Vec2<T>& v)
	{
		return Vec2<T>(m_x - v.m_x , m_y - v.m_y );
	}

	bool operator ==(const Vec2<T>& v)
	{
		if ((m_x == v.m_x ) && (m_y == v.m_y ))
		{
			return true;
		}
		return false;
	}

	bool operator !=(const Vec2<T>& v)
	{
		if ((m_x != v.m_x ) && (m_y != v.m_y ))
		{
			return true;
		}
		return false;
	}

	bool operator>(const Vec2<T>& v) const
	{
		T myArea = m_x * m_y;
		T vArea = v.m_x  * v.m_y ;
		if (myArea > vArea)
		{
			return true;
		}
		return false;
	}

private:
	T m_x;
	T m_y;
};

typedef Vec2<int> Vector2Di;
typedef Vec2<float> Vector2Df;

#endif /* defined( __Vector2D__ ) */