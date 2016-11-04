#pragma once
//------------------------------------------------------------------------
//
//  Name:		Camera2D.h
//
//  Desc:		For view transform related with screen, world and player.
//			
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

#include "Math\Transformations.h"
#include "Utils.h"
#include <iostream>

class Camera2D
{
public:
	static void staticInit(float screenX, float screenY);
	static std::unique_ptr<Camera2D> instance;

	inline Vec2 getOrigin() const { return _origin; }
	inline void setOrigin(const Vec2& origin) { _origin = origin; }
	inline Vec2 getAxisX() const { return _axisX; }
	inline Vec2 getAxisY() const { return _axisY; }
	inline Vec2 getScale() const { return _scale; }
	inline float getRenderRadius() const { return _renderRadius; }
	
	inline void setScale(Vec2 scale) 
	{
		if(scale.x > 0 && scale.y > 0)
		_scale = scale; 
	}

	inline void setCamera(const Vec2& origin, const Vec2& axisX, const Vec2& axisY, Vec2 scale)
	{
		_origin = origin;
		_axisX = axisX;
		_axisY = axisY;
		_scale = scale;
		_renderRadius = std::sqrt((_screenX * _screenX / 4) + (_screenY * _screenY / 4));
	}

	inline bool pointInScreen(const Vec2& screenPos)
	{
		return
			0 < screenPos.x && screenPos.x < _screenX &&
			0 < screenPos.y && screenPos.y < _screenY;
	}

	inline bool segmentInScreen(const Vec2& world_a, const Vec2& world_b)
	{
		Vec2 screen_origin(_screenX / 2, _screenY / 2);
		Vec2 screen_a = worldToScreen(world_a);
		Vec2 screen_b = worldToScreen(world_b);
		return distToSegmentSq(screen_a, screen_b, screen_origin) < _renderRadius * _renderRadius;
	}

	inline bool circleInScreen(const Vec2& world_pos, float world_radius)
	{
		Vec2 screen_origin(_screenX / 2, _screenY / 2);
		Vec2 screen_pos = worldToScreen(world_pos);
		float screen_radius = world_radius * _scale.x;

		return screen_pos.distance(screen_origin) < _renderRadius + screen_radius;
	}


	inline float getScreenX() const { return _screenX; }
	inline float getScreenY() const { return _screenY; }

	Camera2D(float screenX, float screenY);

	Vec2 worldToScreen(const Vec2& pos);
	Vec2 screenToWorld(const Vec2& mpos);


private:
	float _screenX;
	float _screenY;

	Vec2 _origin;
	Vec2 _axisX;
	Vec2 _axisY;
	Vec2 _scale;
	float _renderRadius;
};