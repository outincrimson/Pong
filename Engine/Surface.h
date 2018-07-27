#pragma once
#include "Colors.h"
#include "Rect.h"
#include <string>

class Surface
{
public:
	Surface( const std::string& filename );
	Surface( int width,int height );
	Surface( const Surface& rhs);
	~Surface();
	Surface& operator=( const Surface& );
	void put_pixel( int x,int y,Color c );
	Color get_pixel( int x,int y ) const;
	int get_width() const;
	int get_height() const;

	void floodfill( int x, int y, Color target, Color replace );
	constexpr RectI get_rect() const
	{
		return RectI(0, width, 0, height);
	}
private:
	Color* p_pixels = nullptr;
	int width;
	int height;
};