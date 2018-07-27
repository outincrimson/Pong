#pragma once
#include "Graphics.h"
#include "Paddle.h"


// No balls, real men play pong with bricks
class Brick
{
public:

	Brick() = default;
	Brick(Vec2f pos)
		:
		pos(pos)
	{ }

	int col_sign(float val)
	{
		if(val < 0.0f)
		{
			return -1;
		}
		if(val > 0.0f)
		{
			return 1;
		}
		return 0;
	}
	void Handle_collision(const Paddle& p, float dt)
	{
		if(GetRect().is_overlapping(p.GetRect()))
		{
			auto paddle_pos = p.GetPos();
			if(vel.x > 0.0f)
			{
				if((col_sign(vel.x) != col_sign((pos - paddle_pos).x)) ||
					(pos.x <= paddle_pos.x && pos.x + width > paddle_pos.x)&& pos.x+width <= paddle_pos.x+p.GetWidth())
				{
					vel.x = -vel.x;
				}
				else
				{
					auto prec = pos - paddle_pos;
					vel.y = -vel.y;
				}
			}
			else if(vel.x < 0.0f)
			{

				if((col_sign(vel.x) != col_sign((pos - paddle_pos).x)) ||
					(pos.x+width >= paddle_pos.x+p.GetWidth() && pos.x <= paddle_pos.x+p.GetWidth() && pos.x >= paddle_pos.x))
				{
					vel.x = -vel.x;
				}
				else
				{
					vel.y = -vel.y;
				}
			}
			vel = vel * speed_up_factor;
		}
	}

	void Update(float dt)
	{
		pos += vel * dt;

		if(pos.x < 0.0f || pos.x + width >= Graphics::ScreenWidth)
		{
			on_screen = false;
		}
		if(pos.y < 0.0f)
		{
			pos.y = 0.0f;
			vel.y = -vel.y;
		}
		else if(pos.y + height >= Graphics::ScreenHeight)
		{
			pos.y = Graphics::ScreenHeight - height - 1;
			vel.y = -vel.y;
		}
	}

	void Draw(Graphics& gfx)
	{
		if(on_screen)
		{
			gfx.DrawRect(GetRect());
		}
	}

	RectI GetRect() const
	{
		return Rectangle_<int>::MakeRectangle((Vec2i)pos, width, height);
	}
private:
	static constexpr float speed_up_factor = 1.05f;

	Vec2f pos;

	Vec2f vel = { 400.0f,400.0f };
	float width = 10.0f;
	float height = 10.0f;
	bool on_screen = true;
};