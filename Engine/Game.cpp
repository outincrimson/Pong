/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	p1({ (float) Paddle::margin_offset,Graphics::ScreenHeight / 2 - (Paddle::default_height / 2) }),
	p2({ Graphics::ScreenWidth - Paddle::default_width - Paddle::margin_offset,Graphics::ScreenHeight / 2 - (Paddle::default_height / 2) }),
	brick({ Graphics::ScreenWidth / 2,Graphics::ScreenHeight / 2 })
{ }

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while(elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	p1.Update<Paddle::Control_type::control1>(wnd.kbd,dt);
	p2.Update<Paddle::Control_type::control2>(wnd.kbd,dt);
	brick.Update(dt, p1, p2);
}

void Game::ComposeFrame()
{
	p1.Draw(gfx);
	p2.Draw(gfx);
	brick.Draw(gfx);
}
