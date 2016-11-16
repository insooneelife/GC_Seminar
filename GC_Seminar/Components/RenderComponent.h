//------------------------------------------------------------------------
//
//  Name:		RenderComponent.h
//
//  Desc:		Defines renderable component.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include "../Math/Vec2.h"

class Texture;
class IRenderComponent;
class RenderComponent
{
public:

	RenderComponent(IRenderComponent& entity, Texture* texture);

	~RenderComponent();

	void setTexture(Texture* inTexture) { _texture = inTexture; }

	virtual void draw(const SDL_Rect& inViewTransform);

private:

	IRenderComponent& _owner;
	Vec2								_origin;
	Texture*							_texture;
};