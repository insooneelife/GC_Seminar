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
#include <Box2D/Box2D.h>

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
	void			drawSprite(Vec2 pos, Vec2 texture_origin, int width, int height, SDL_Texture* texture);

	void			drawBox2DShape(b2Shape* shape);
	void			addBox2DShape(b2Shape* shape);
	void			addBox2DEdge(Vec2 a, Vec2 b);
	void			addBox2DCircle(Vec2 a, float radius);
	void			addBox2DPolygon(const std::vector<b2Vec2>& points);

	void addRenderable(Renderable* renderable);
	void removeRenderable(Renderable* renderable);
	int getRenderableIndex(Renderable* renderable) const;

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


private:

	GraphicsDriver();
	bool init(SDL_Window* wnd);

	SDL_Renderer*			_renderer;
	SDL_Rect				_view_port;
	TTF_Font*				_font;

	std::vector<Renderable*> _renderables;
	std::vector<b2Shape*> _draw_shapes;

	SDL_Rect mViewTransform;
};
