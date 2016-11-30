#pragma once
//------------------------------------------------------------------------
//
//  Name:   Button.h
//
//  Desc:   UI button
//
//  Author: Insub Im (insooneelife@naver.com)
//
//--------------------------------------------------------------------------

#include "Entity.h"
#include <iostream>

class Button : public Entity
{
public:
	
	inline const std::string& getText() const		{ return _text; }
	inline void setText(const std::string text)		{ _text = text; }
	inline bool isVisible() const					{ return _visible; }
	inline void setVisible(bool visible)			{ _visible = visible; }

	Button(World& world, unsigned int id, const Vec2& pos, const std::string& text);

	virtual ~Button() {}
	virtual bool contains(Vec2 pos) { return (_pos.distance(pos) <= _radius); }
	virtual void update() override;
	virtual void render() override;

private:

	std::string _text;
	bool _visible;
};