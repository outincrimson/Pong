#pragma once
#include "Graphics.h"

enum class Control_type
{
	control1,
	control2
};


template<Control_type control_type>
class Paddle_
{
public:

	Paddle_(Vec2f pos, Color color = Colors::White)
		:
		pos(pos),
		color(color)
	{ }

	void Update(Keyboard& kbd)
	{
		if constexpr(control_type == Control_type::control1)
		{
			if(kbd.KeyIsPressed('W'))
			{
				pos.y -= vel;
			}
			if(kbd.KeyIsPressed('S'))
			{
				pos.y += vel;
			}
		}
		else
		{
			if(kbd.KeyIsPressed(VK_UP))
			{
				pos.y -= vel;
			}
			if(kbd.KeyIsPressed(VK_DOWN))
			{
				pos.y += vel;
			}
		}


		if(pos.y + height >= Graphics::ScreenHeight)
		{
			pos.y = Graphics::ScreenHeight - height - 1;
		}
		else if(pos.y < 0.0f)
		{
			pos.y = 0.0f;
		}
	}

	void Draw(Graphics& gfx) const
	{
		auto paddle_rect = RectI(int(pos.x), int(pos.x + width), int(pos.y), int(pos.y + height));
		gfx.DrawRect(paddle_rect, color);
	}

	auto GetWidth() const
	{
		return width;
	}
	auto GetHeight() const
	{
		return height;
	}

public:
	static constexpr int margin_offset = 15;
	static constexpr float default_width = 10.0f;
	static constexpr float default_height = 115.0f;

private:
	float vel = 6.5f;
	float width = 10.0f;
	float height = 115.0f;

	Vec2f pos;
	Color color;
};



using Paddle = Paddle_<Control_type::control1>;