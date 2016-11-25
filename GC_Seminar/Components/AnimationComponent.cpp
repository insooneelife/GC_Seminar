#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "Interfaces.h"
#include "../TextureManager.h"
#include <sstream>
#include <iostream>

AnimationComponent::AnimationComponent(IAnimationComponent& entity, int max_directions)
	:
	_owner(entity),
	_frame(0),
	_max_frame(1),
	_max_directions(max_directions)
{}

bool AnimationComponent::frameCount()
{
	_frame++;
	if (_frame % _max_frame == 0)
	{
		_frame = 0;
		return true;
	}
	return false;
}


BaseAnimation::BaseAnimation(IAnimationComponent& entity, int max_directions)
	:
	AnimationComponent(entity, max_directions)
{
	setAction("Idle");
}

void BaseAnimation::setAction(const std::string& action)
{
	_frame = 0;
	_action = action;
	_max_frame = 5;
}

bool BaseAnimation::updateAnimation(RenderComponent& sprite)
{
	std::stringstream ss;
	ss << _frame;
	std::string tname = _owner.getName() + _action + ss.str();

	std::cout << _frame << " " << tname << std::endl;

	sprite.setTexture(&TextureManager::instance->getTexture(tname));
	return frameCount();
}


NoneAnimation::NoneAnimation(IAnimationComponent& entity, int max_directions)
	:
	AnimationComponent(entity, max_directions)
{}

void NoneAnimation::setAction(const std::string& action)
{}

bool NoneAnimation::updateAnimation(RenderComponent& sprite)
{
	return true;
}