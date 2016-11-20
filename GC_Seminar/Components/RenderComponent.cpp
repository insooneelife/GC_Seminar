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
		GraphicsDriver::instance->drawSprite(
			_owner.getPos(),
			_origin,
			_texture->GetWidth(),
			_texture->GetHeight(),
			_texture->GetData());
	}
}