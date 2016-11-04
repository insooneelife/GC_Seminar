#pragma once
//------------------------------------------------------------------------
//
//  Name:		GraphicsDriver.h
//
//  Desc:		Utility class for wrapping SDL graphic tools
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>
#include <vector>
#include "Math/Vec2.h"
#include <Box2D/Common/b2Draw.h>

#include <Windows.h>
#include <GL/gl.h>

class Renderable;
class GraphicsDriver : public b2Draw
{
public:

	static bool staticInit(SDL_Window* wnd);

	static std::unique_ptr< GraphicsDriver > instance;

	static SDL_Color red;
	static SDL_Color blue;
	static SDL_Color yellow;
	static SDL_Color black;
	static SDL_Color white;

	static SDL_Color green;				
	static SDL_Color indigo;			
	static SDL_Color darkgray;			
	static SDL_Color orange; 			
	static SDL_Color antiquewhite;		
	static SDL_Color lemon; 			
	static SDL_Color darkgreen;


	void			render();
	void			clear();
	void			present();
	SDL_Rect&		getLogicalViewport();
	SDL_Renderer*	getRenderer();

	void			drawPoint(Vec2 p, SDL_Color color = red, bool on_ui = false);
	void			drawLine(Vec2 a, Vec2 b, SDL_Color color = red, bool on_ui = false);
	void			drawRect(Vec2 p, float w, float h, SDL_Color color = red, bool on_ui = false);
	void			drawCircle(Vec2 p, float r, SDL_Color color = red, float fragment = 10, bool on_ui = false);
	void			drawText(const std::string& str, Vec2 p, const SDL_Color& color = red, bool on_ui = false);

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
	static inline Vec2 toVec(const Point& p) { return Vec2(p.x, p.y); }

	template<typename Point>
	static inline b2Vec2 tob2Vec(const Point& p) { return b2Vec2(p.x, p.y); }

	template<typename Color>
	static inline b2Color tob2Color(const Color& sdl_color)
	{
		return b2Color(sdl_color.r, sdl_color.g, sdl_color.b, sdl_color.a);
	}

	template<typename Color>
	static inline void toSdlColor(SDL_Color& sdl_color, const Color& b2_color)
	{
		sdl_color.r = (Uint8)(b2_color.r * 255.0f);
		sdl_color.g = (Uint8)(b2_color.g * 255.0f);
		sdl_color.b = (Uint8)(b2_color.b * 255.0f);
		sdl_color.a = (Uint8)(b2_color.a * 255.0f);
	}

	void addRenderable(Renderable* renderable);
	void removeRenderable(Renderable* renderable);
	int getRenderableIndex(Renderable* renderable) const;

private:

	GraphicsDriver();
	bool init(SDL_Window* wnd);

	SDL_Renderer*			_renderer;
	SDL_Rect				_view_port;
	TTF_Font*				_font;

	std::vector<Renderable*> _renderables;

	SDL_Rect mViewTransform;
};
