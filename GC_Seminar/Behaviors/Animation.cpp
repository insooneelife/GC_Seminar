#include "starcraft.h"

Animation::Animation(IAnimation& entity, int max_directions)
	:
	_owner(entity),
	_frame(0),
	_max_frame(1),
	_max_directions(max_directions)
{}

bool Animation::frameCount()
{
	_frame++;
	if (_frame % _max_frame == 0)
	{
		_frame = 0;
		return true;
	}
	return false;
}


BaseAnimation::BaseAnimation(IAnimation& entity, int max_directions)
	:
	Animation(entity, max_directions)
{
	setAction("Idle");
}

void BaseAnimation::setAction(const std::string& action)
{
	_frame = 0;
	_action = action;
	_max_frame = Database::instance->getAnimationData(_owner.getName()).getMaxFrame(action);
}

bool BaseAnimation::updateAnimation(Renderable& sprite, const std::string& texture_name)
{
	std::stringstream ss;
	ss << _frame;
	std::string tname = _owner.getName() + _action + ss.str();

	std::cout << _frame << " " << tname << std::endl;

	sprite.setTexture(TextureManager::sInstance->GetTexture(tname));
	return frameCount();
}


NoneAnimation::NoneAnimation(IAnimation& entity, int max_directions)
	:
	Animation(entity, max_directions)
{}

void NoneAnimation::setAction(const std::string& action)
{}

bool NoneAnimation::updateAnimation(Renderable& sprite, const std::string& texture_name)
{
	return true;
}