#include "Renderable.h"
#include "GraphicsDriver.h"
#include "Entity/Entity.h"
#include "Texture.h"
#include "Math/Vec2.h"

Renderable::Renderable(Entity* entity, Texture* texture)
	:
	_owner(entity),
	_texture(texture)
{
	_origin = Vec2(texture->GetWidth() * 0.5f, texture->GetHeight() * 0.5f);

	//and add yourself to the rendermanager...
	GraphicsDriver::instance->addRenderable(this);
}

Renderable::~Renderable()
{
	//don't render me, I'm dead!
	GraphicsDriver::instance->removeRenderable(this);
}

#include <iomanip>
void Renderable::draw(const SDL_Rect& veiw_transform)
{
	if (_texture)
	{
		Vec2 renderPos = Vec2(-_origin.x, _origin.y) + _owner->getPos();

		// Compute the destination rectangle
		Vec2 location = _owner->getPos();

		SDL_Rect dstRect;
		dstRect.w = static_cast< int >(_texture->GetWidth());
		dstRect.h = static_cast< int >(_texture->GetHeight());
		dstRect.x = veiw_transform.x + static_cast< int >(renderPos.x);
		dstRect.y = veiw_transform.y - static_cast< int >(renderPos.y);

		SDL_Renderer* render = GraphicsDriver::instance->getRenderer();

		// Blit the texture
		SDL_RenderCopyEx(render, _texture->GetData(), nullptr,
			&dstRect, 0, nullptr, SDL_FLIP_NONE);
	}
}