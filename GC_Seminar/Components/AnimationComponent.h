#include <string>
//------------------------------------------------------------------------
//
//  Name:		AnimationComponent.h
//
//  Desc:		Animation module.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

class RenderComponent;
class IAnimationComponent;
class AnimationComponent
{
public:
	inline std::string getAction() const	{ return _action; }

	inline int getFrame() const				{ return _frame; }
	inline void setFrame(int value)			{ _frame = value; }

	inline int getMaxFrame() const			{ return _max_frame; }
	inline void setMaxFrame(int value)		{ _max_frame = value; }

	inline int getMaxDirections() const		{ return _max_directions; }
	inline void setMaxDirections(int value)	{ _max_directions = value; }

	AnimationComponent(IAnimationComponent& entity, int maxDirections);

	bool frameCount();

	virtual void setAction(const std::string& action) = 0;
	virtual bool updateAnimation(RenderComponent& sprite) = 0;

protected:
	IAnimationComponent& _owner;
	std::string _action;
	int _frame;
	int _max_frame;
	int _max_directions;
};


class BaseAnimation : public AnimationComponent
{
public:
	BaseAnimation(IAnimationComponent& entity, int max_directions);

	virtual void setAction(const std::string& action) override;

	virtual bool updateAnimation(RenderComponent& sprite) override;
};

class NoneAnimation : public AnimationComponent
{
public:

	NoneAnimation(IAnimationComponent& entity, int max_directions);

	virtual void setAction(const std::string& action) override;

	virtual bool updateAnimation(RenderComponent& sprite) override;
};