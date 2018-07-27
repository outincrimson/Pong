#pragma once
#include "Vector2.h"

template<typename T>
class Rectangle_
{
public:
	Rectangle_() = default;
	constexpr Rectangle_(T in_left, T in_right, T in_top, T in_bottom)
		:
		left(in_left),
		right(in_right),
		top(in_top),
		bottom(in_bottom)
	{ }
	constexpr Rectangle_(const Vector2<T>& in_top_left, const Vector2<T>& in_bottom_right)
		:
		Rectangle_(in_top_left.x, in_bottom_right.x, in_top_left.y, in_bottom_right.y)
	{ }
	constexpr Rectangle_(const Vector2<T>& in_top_left, T in_width, T in_height)
		:
		Rectangle_(in_top_left, in_top_left + Vector2<T>(in_width, in_height))
	{ }

	constexpr bool operator==(const Rectangle_& rhs) const
	{
		return left == rhs.left && right == rhs.right &&
			top == rhs.top && bottom == rhs.bottom;
	}
	constexpr bool operator!=(const Rectangle_& rhs) const
	{
		return !(*this == rhs);
	}

	constexpr bool is_overlapping(const Rectangle_& other) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}

	static constexpr Rectangle_ FromCenter(const Vector2<T> & center, T width, T height)
	{
		width /= (T) 2;
		height /= (T) 2;
		const Vector2<T> half(width, height);
		return Rectangle_(center - half, center + half);
	}
	static constexpr Rectangle_ MakeRectangle(const Vector2<T>& v, T width, T height)
	{
		return Rectangle_(v.x, v.x + width, v.y, v.y + height);
	}

public:
	T left;
	T right;
	T top;
	T bottom;
};

using RectI = Rectangle_<int>;
using RectU = Rectangle_<unsigned int>;
using RectF = Rectangle_<float>;
using RectD = Rectangle_<double>;