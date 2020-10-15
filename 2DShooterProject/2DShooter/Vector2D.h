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

	T getX() const { return m_x; }

	T getY() const { return m_y; }

	T* getXPtr() { return &m_x; }

	T* getYPtr() { return &m_y; }

	T& getXRef() { return m_x; }

	T& getYRef() { return m_y; }

	T Lenght() { return sqrt(SquareLenght()); }

	T SquareLenght() { return (m_x * m_x) + (m_y * m_y); }

	bool operator==(const Vec2<T>& v) { return ((m_x == v.m_x) && (m_y == v.m_y)) ? true : false; }

	bool operator!=(const Vec2<T>& v) { return ((m_x != v.m_x) && (m_y != v.m_y)) ? true : false; }

	bool operator>(const Vec2<T>& v) const { return ((m_x * m_y) > (v.m_x * v.m_y)) ? true : false; }

	bool operator<(const Vec2<T>& v) const { return ((m_x * m_y) < (v.m_x * v.m_y)) ? true : false; }

	Vec2<T> operator*(T f) const { return Vec2(m_x * f, m_y * f); }

	Vec2<T> operator%(T f) const { return Vec2(m_x % f, m_y % f); }

	Vec2<T> operator+(const Vec2<T>& v) { return Vec2<T>(m_x + v.m_x, m_y + v.m_y); }

	Vec2<T> operator-(const Vec2<T>& v) { return Vec2<T>(m_x - v.m_x, m_y - v.m_y); }

	void operator+=(const Vec2<T>& v)
	{
		m_x += v.m_x ;
		m_y += v.m_y ;
	}

	void operator-=(const Vec2<T>& v)
	{
		m_x -= v.m_x ;
		m_y -= v.m_y ;
	}

private:
	T m_x;
	T m_y;
};

typedef Vec2<int> Vector2Di;
typedef Vec2<float> Vector2Df;


template <class T>
struct Dimentions
{
	Dimentions(T x = 0, T y = 0)
	{
		m_vecDimentions.getXRef() = x;
		m_vecDimentions.getYRef() = y;
	}

	
	T getWidth() const { return m_vecDimentions.getX(); }
	T getHeight() const { return m_vecDimentions.getY(); }

	T& getWidthRef() { return m_vecDimentions.getXRef(); }
	T& getHeightRef() { return m_vecDimentions.getYRef(); }

	T* getWidthPtr() { return m_vecDimentions.getXPtr(); }
	T* getHeightPtr() { return m_vecDimentions.getYPtr(); }
	


	T Lenght() { return m_vecDimentions.SquareLenght(); }

	T SquareLenght() { return m_vecDimentions.SquareLenght(); }

	bool operator==(const Dimentions<T>& d) { return (m_vecDimentions == d.m_vecDimentions); }

	bool operator!=(const Dimentions<T>& d) { return (m_vecDimentions != d.m_vecDimentions); }

	bool operator>(const Dimentions<T>& d) const { return (m_vecDimentions > d.m_vecDimentions); }

	bool operator<(const Dimentions<T>& d) const { return (m_vecDimentions < d.m_vecDimentions); }

	Dimentions<T> operator*(T f) const { return m_vecDimentions * f ; }

	Dimentions<T> operator%(T f) const { return m_vecDimentions % f; }

	Dimentions<T> operator+(const Dimentions<T>& d) { return m_vecDimentions + d.m_vecDimentions;	}

	Dimentions<T> operator-(const Dimentions<T>& d) {	return m_vecDimentions - d.m_vecDimentions;	}

	void operator+=(const Dimentions<T>& d) { m_vecDimentions += d.m_vecDimentions; }

	void operator-=(const Dimentions<T>& d) { m_vecDimentions -= d.m_vecDimentions; }

private:
	Vec2<T> m_vecDimentions;
};

typedef Dimentions<int> Dimention2Di;
typedef Dimentions<float> Dimention2Df;


#endif /* defined( __Vector2D__ ) */