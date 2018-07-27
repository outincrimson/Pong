#pragma once
#include "Vector2.h"

template<typename T>
class Rectangle
{
public:
	Rectangle() = default;
	constexpr Rectangle( T in_left, T in_right, T in_top, T in_bottom )
		:
		left( in_left ),
		right( in_right ),
		top( in_top ),
		bottom( in_bottom )
	{ }
	constexpr Rectangle( const Vector2<T>& in_top_left, const Vector2<T>& in_bottom_right )
		:
		Rectangle( in_top_left.x, in_bottom_right.x, in_top_left.y, in_bottom_right.y )
	{ }
	constexpr Rectangle( const Vector2<T>& in_top_left, T in_width, T in_height )
		:
		Rectangle( in_top_left, in_top_left + Vector2<T>( in_width, in_height ) )
	{ }

	constexpr bool operator==( const Rectangle& rhs ) const
	{
		return left == rhs.left && right == rhs.right &&
			top == rhs.top && bottom == rhs.bottom;
	}
	constexpr bool operator!=( const Rectangle& rhs ) const
	{
		return !(*this == rhs);
	}

	constexpr bool is_overlapping( const Rectangle& other ) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}

	static constexpr Rectangle FromCenter( const Vector2<T> & center, T width, T height )
	{
		width /= (T) 2;
		height /= (T) 2;
		const Vector2<T> half( width, height );
		return Rectangle( center - half, center + half );
	}
	static constexpr Rectangle MakeRectangle( const Vector2<T>& v, T width, T height )
	{
		return Rectangle( v.x, v.x + width, v.y, v.y + height );
	}

public:
	T left;
	T right;
	T top;
	T bottom;
};

using RectD = Rectangle<double>;
using RectF = Rectangle<float>;
using RectI = Rectangle<int>;
using RectU = Rectangle<unsigned int>;