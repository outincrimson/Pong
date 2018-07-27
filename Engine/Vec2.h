#pragma once
#include "Matrix.h"

template<typename T>
class Vector2
{
public:
	Vector2() = default;
	constexpr Vector2( T in_x, T in_y ) noexcept
		:
	x( in_x ), y( in_y )
	{ }

	template<typename U>
	explicit constexpr operator Vector2<U>() const noexcept
	{
		return { (U) x,(U) y };
	}

	constexpr Vector2 operator+( const Vector2& rhs ) const
	{
		return Vector2( x + rhs.x, y + rhs.y );
	}
	constexpr Vector2& operator+=( const Vector2& rhs )
	{
		return *this = *this + rhs;
	}
	constexpr Vector2 operator-( const Vector2& rhs ) const
	{
		return Vector2( x - rhs.x, y - rhs.y );
	}
	constexpr Vector2& operator-=( const Vector2& rhs )
	{
		return *this = *this - rhs;
	}
	constexpr Vector2 operator*( T rhs ) const
	{
		return Vector2( x*rhs, y*rhs );
	}
	constexpr Vector2& operator*=( T rhs )
	{
		return *this = *this*rhs;
	}

	constexpr Vector2 operator-() const
	{
		return { -x,-y };
	}

	constexpr T operator*( const Vector2& rhs ) const
	{
		return x * rhs.x + y * rhs.y;
	}


	constexpr Vector2 operator*( const Matrix<T, 2>& rhs ) const
	{
		return
		{
			x * rhs[0][0] + y * rhs[1][0],
			x * rhs[0][1] + y * rhs[1][1]
		};
	}
	constexpr Vector2& operator*=( const Matrix<T, 2>& rhs )
	{
		return *this = *this * rhs;
	}

	constexpr bool operator==( const Vector2& rhs ) const
	{
		return x == rhs.x && y == rhs.y;
	}
	constexpr bool operator!=( const Vector2& rhs ) const
	{
		return !(*this == rhs);
	}

	constexpr Vector2& normalize()
	{
		return *this = this->get_normalized();
	}
	constexpr Vector2 get_normalized() const
	{
		const T len = get_length();
		if(len != 0)
		{
			return *this * (1 / len);
		}
		return *this;
	}

	constexpr T get_length() const
	{
		return std::sqrt( x*x + y*y );
	}
	constexpr T get_length_sq() const
	{
		return x*x + y*y;
	}

public:
	T x;
	T y;

};

using Vec2d = Vector2<double>;
using Vec2f = Vector2<float>;
using Vec2i = Vector2<int>;
using Vec2u = Vector2<unsigned int>;