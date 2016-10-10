#include <iostream>
#include <sstream>
#include "Button.h"
#include "../Entity/Hunter.h"
#include "../World.h"
#include "../GraphicsDriver.h"

Button::Button(World& world, unsigned int id, const Vec2& pos, const std::string& text)
	:
	Entity(world, id, pos, 40.0f, Entity::Type::kButton, GraphicsDriver::blue),
	_text(text),
	_visible(false)
{}

void Button::update()
{
	std::cout << _text << " button selected" << std::endl;
	if (_text == "Damage")
		_world.getPlayerEntity()->upgradeDamage();

	else if(_text == "Range")
		_world.getPlayerEntity()->upgradeRange();
}

void Button::render()
{
	if (!_visible)
		return;
	GraphicsDriver::instance->drawCircle(_pos, _radius, _color, 15.0f, true);
	GraphicsDriver::instance->drawText(_text, _pos, _color, true);
}

