//------------------------------------------------------------------------
//
//  Name:		GraphicsDriver.h
//
//  Desc:		Utility class for wrapping SDL graphic tools
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------


#pragma once

#include <SDL/SDL.h>
#include <SDL\SDL_ttf.h>
#include <memory>
#include "Math\Vec2.h"

class GraphicsDriver
{
public:

	static bool staticInit(SDL_Window* wnd);

	static std::unique_ptr< GraphicsDriver > instance;

	static SDL_Color red;
	static SDL_Color blue;
	static SDL_Color yellow;


	void			clear();
	void			present();
	SDL_Rect&		getLogicalViewport();
	SDL_Renderer*	getRenderer();

	void			drawLine(Vec2 a, Vec2 b, SDL_Color color = red);
	void			drawRect(Vec2 p, float w, float h, SDL_Color color = red);
	void			drawCircle(Vec2 p, float r, float fragment = 15, SDL_Color color = red);
	void			drawText(const std::string& inStr, const Vec2& origin, const SDL_Color& inColor = red);

	~GraphicsDriver();

private:

	GraphicsDriver();
	bool init(SDL_Window* wnd);

	SDL_Renderer*			_renderer;
	SDL_Rect				_view_port;
	TTF_Font*				_font;
};
