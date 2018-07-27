#pragma once
#include "Graphics.h"



class Paddle
{
public:
	enum class Control_type
	{
		control1,
		control2
	};
public:
	Paddle(Vec2f pos, Color color = Colors::White)
		:
		pos(pos),
		color(color)
	{ }


	template<Control_type type>
	void Update(Keyboard& kbd, float dt)
	{
		if constexpr(type == Control_type::control1)
		{
			if(kbd.KeyIsPressed('W'))
			{
				pos.y -= vel*dt;
			}
			if(kbd.KeyIsPressed('S'))
			{
				pos.y += vel*dt;
			}
		}
		else
		{
			if(kbd.KeyIsPressed(VK_UP))
			{
				pos.y -= vel*dt;
			}
			if(kbd.KeyIsPressed(VK_DOWN))
			{
				pos.y += vel*dt;
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

	RectI GetRect() const
	{
		return RectI::MakeRectangle((Vec2i) pos, width, height);
	}

	auto GetWidth() const
	{
		return width;
	}
	auto GetHeight() const
	{
		return height;
	}

	Vec2f GetPos() const
	{
		return pos;
	}

public:
	static constexpr int margin_offset = 15;
	static constexpr float default_width = 15.0f;
	static constexpr float default_height = 115.0f;

private:
	float vel = 400.5f;
	float width = 15.0f;
	float height = 115.0f;

	Vec2f pos;
	Color color;
};
