#include "starcraft.h"

Renderable::Renderable(IRenderable& entity, TexturePtr texture)
	:
	_owner(entity),
	_texture(texture)
{
	_origin = Vec2(texture->GetWidth() * 0.5f, texture->GetHeight() * 0.5f);

	//and add yourself to the rendermanager...
	RenderManager::sInstance->addRenderable(this);
}

Renderable::~Renderable()
{
	//don't render me, I'm dead!
	RenderManager::sInstance->removeRenderable(this);
}

#include <iomanip>
void Renderable::draw(const SDL_Rect& inViewTransform)
{
	if (_texture)
	{
		Vec2 renderPos = Vec2(-_origin.x, _origin.y) + _owner.getPos();

		// Compute the destination rectangle
		Vec2 location = _owner.getPos();

		SDL_Rect dstRect;
		dstRect.w = static_cast< int >(_texture->GetWidth());
		dstRect.h = static_cast< int >(_texture->GetHeight());
		dstRect.x = inViewTransform.x + static_cast< int >(renderPos.x);
		dstRect.y = inViewTransform.y - static_cast< int >(renderPos.y);

		SDL_Renderer* render = GraphicsDriver::sInstance->GetRenderer();

		// Blit the texture
		SDL_RenderCopyEx(render, _texture->GetData(), nullptr,
			&dstRect, 0, nullptr, SDL_FLIP_NONE);
	}
}