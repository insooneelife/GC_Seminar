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

#include <Box2D\Common\b2Draw.h>

class GraphicsDriver : public b2Draw
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

	void			drawPoint(Vec2 p, SDL_Color color = red);
	void			drawLine(Vec2 a, Vec2 b, SDL_Color color = red);
	void			drawRect(Vec2 p, float w, float h, SDL_Color color = red);
	void			drawCircle(Vec2 p, float r, float fragment = 15, SDL_Color color = red);
	void			drawText(const std::string& inStr, const Vec2& origin, const SDL_Color& inColor = red);

	virtual ~GraphicsDriver();

	// Box2D drawing functions.
	/// Draw a closed polygon provided in CCW order.
	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

	/// Draw a solid closed polygon provided in CCW order.
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

	/// Draw a circle.
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;

	/// Draw a solid circle.
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;

	/// Draw a line segment.
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

	/// Draw a transform. Choose your own length scale.
	/// @param xf a transform.
	virtual void DrawTransform(const b2Transform& xf) override;

	/// Draw a point.
	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

	// Helper
	template<typename Point>
	inline Vec2 toVec(const Point& p) { return Vec2(p.x, p.y); }

	template<typename Point>
	inline b2Vec2 tob2Vec(const Point& p) { return b2Vec2(p.x, p.y); }

	template<typename Color>
	inline b2Color tob2Color(const Color& sdl_color)
	{
		return b2Color(sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
	}

	template<typename Color>
	inline void toSdlColor(SDL_Color& sdl_color, const Color& b2_color)
	{
		sdl_color.r = b2_color.r;
		sdl_color.g = b2_color.g;
		sdl_color.b = b2_color.b;
		sdl_color.a = b2_color.a;
	}
	

private:

	GraphicsDriver();
	bool init(SDL_Window* wnd);

	SDL_Renderer*			_renderer;
	SDL_Rect				_view_port;
	TTF_Font*				_font;
};
