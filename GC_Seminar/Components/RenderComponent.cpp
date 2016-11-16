#include <SDL/SDL.h>
#include "RenderComponent.h"
#include "Interfaces.h"
#include "../GraphicsDriver.h"
#include "../Texture.h"
#include "../Camera2D.h"

RenderComponent::RenderComponent(IRenderComponent& entity, Texture* texture)
	:
	_owner(entity),
	_texture(texture)
{
	_origin = Vec2(texture->GetWidth() * 0.5f, texture->GetHeight() * 0.5f);

	//and add yourself to the rendermanager...
	GraphicsDriver::instance->addRenderable(this);
}

RenderComponent::~RenderComponent()
{
	//don't render me, I'm dead!
	GraphicsDriver::instance->removeRenderable(this);
}

#include <iomanip>
#include <iostream>

void RenderComponent::draw(const SDL_Rect& veiw_transform)
{
	if (_texture)
	{
		Vec2 pos = Camera2D::instance->worldToScreen(_owner.getPos());
		Vec2 renderPos = Vec2(-_origin.x, -_origin.y) + pos;

		SDL_Rect dstRect;
		dstRect.w = static_cast< int >(_texture->GetWidth());
		dstRect.h = static_cast< int >(_texture->GetHeight());
		dstRect.x = veiw_transform.x + static_cast< int >(renderPos.x);
		dstRect.y = veiw_transform.y + static_cast< int >(renderPos.y);

		SDL_Renderer* render = GraphicsDriver::instance->getRenderer();


		// Blit the texture
		SDL_RenderCopyEx(render, _texture->GetData(), nullptr,
			&dstRect, 0, nullptr, SDL_FLIP_NONE);
	}
}