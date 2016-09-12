//------------------------------------------------------------------------
//
//  Name:		Renderable.h
//
//  Desc:		Defines renderable component.
//
//  Author:		Insub Im (insooneelife@naver.com)
//
//------------------------------------------------------------------------


class IRenderable;
class Renderable
{
public:

	Renderable(IRenderable& entity, TexturePtr texture);

	~Renderable();

	void setTexture(TexturePtr inTexture) { _texture = inTexture; }

	virtual void draw(const SDL_Rect& inViewTransform);

private:

	IRenderable& _owner;
	Vec2								_origin;
	TexturePtr							_texture;
};