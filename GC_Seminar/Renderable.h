//------------------------------------------------------------------------
//
//  Name:		Renderable.h
//
//  Desc:		Defines renderable component.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include <memory>
#include <SDL/SDL.h>
#include "Math/Vec2.h"

class Texture;
class Entity;
class Renderable
{
public:

	Renderable(Entity* entity, Texture* texture);

	~Renderable();

	void setTexture(Texture* texture) { _texture = texture; }

	virtual void draw(const SDL_Rect& veiw_transform);

private:

	Entity* _owner;
	Vec2 _origin;
	Texture* _texture;
};