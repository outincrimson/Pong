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
	bool Handle_collision(Paddle& p, float dt)
	{
		if(!p.is_on_cooldown() && GetRect().is_overlapping(p.GetRect()))
		{
			auto paddle_pos = p.GetPos();
			if(vel.x > 0.0f)
			{
				if((col_sign(vel.x) != col_sign((pos - paddle_pos).x)) ||
					(pos.x <= paddle_pos.x && pos.x + width >= paddle_pos.x)&& pos.x+width <= paddle_pos.x+p.GetWidth())
				{
					vel.x = -vel.x;
				}
				else
				{
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
			p.set_on_cooldown();
			return true;
		}
		return false;
	}
	
	void Update(float dt, Paddle& p1, Paddle& p2)
	{
		auto next_pos_offset = vel * dt;
		if(vel.x < 0.0f)
		{
			for(int i = 0; i < 5; i++)
			{
				pos += next_pos_offset / 5.0f;
				if(Handle_collision(p1, dt))
				{
					if(p2.is_on_cooldown())
					{
						p2.set_off_cooldown();
					}
					break;
				}
			}
		}
		else
		{
			for(int i = 0; i < 5; i++)
			{
				pos += next_pos_offset / 5.0f;
				if(Handle_collision(p2, dt))
				{
					if(p1.is_on_cooldown())
					{
						p1.set_off_cooldown();
					}
					break;
				}
			}
		}

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
		return Rectangle_<int>::MakeRectangle((Vec2i)pos, (int)width, (int)height);
	}
private:
	static constexpr float speed_up_factor = 1.05f;

	Vec2f pos;

	Vec2f vel = { 500.0f,500.0f };
	float width = 10.0f;
	float height = 10.0f;
	bool on_screen = true;
};