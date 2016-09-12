//------------------------------------------------------------------------
//
//  Name:		Animation.h
//
//  Desc:		Animation module.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------

class IAnimation;
class Animation
{
public:
	inline std::string getAction() const	{ return _action; }

	inline int getFrame() const				{ return _frame; }
	inline void setFrame(int value)			{ _frame = value; }

	inline int getMaxFrame() const			{ return _max_frame; }
	inline void setMaxFrame(int value)		{ _max_frame = value; }

	inline int getMaxDirections() const		{ return _max_directions; }
	inline void setMaxDirections(int value)	{ _max_directions = value; }

	Animation(IAnimation& entity, int maxDirections);

	bool frameCount();

	virtual void setAction(const std::string& action) = 0;
	virtual bool updateAnimation(Renderable& sprite, const std::string& name) = 0;

protected:
	IAnimation& _owner;
	std::string _action;
	int _frame;
	int _max_frame;
	int _max_directions;
};


class BaseAnimation : public Animation
{
public:
	BaseAnimation(IAnimation& entity, int max_directions);

	virtual void setAction(const std::string& action) override;

	virtual bool updateAnimation(Renderable& sprite, const std::string& texture_name) override;
};

class NoneAnimation : public Animation
{
public:

	NoneAnimation(IAnimation& entity, int max_directions);

	virtual void setAction(const std::string& action) override;

	virtual bool updateAnimation(Renderable& sprite, const std::string& texture_name) override;
};