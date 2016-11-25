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
#include <SDL/SDL.h>

class Texture;
class IRenderComponent;
class RenderComponent
{
public:

	RenderComponent(IRenderComponent& entity, const Texture* texture);
	~RenderComponent();

	inline void setTexture(const Texture* texture) { _texture = texture; }
	virtual void draw(const SDL_Rect& inViewTransform);

private:

	IRenderComponent& _owner;
	Vec2 _origin;
	const Texture* _texture;
};