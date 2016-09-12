#pragma once

#include <SDL\SDL.h>
#include <memory>

class Texture
{
public:
	Texture( uint32_t inWidth, uint32_t inHeight, SDL_Texture* inTexture );
	~Texture();

	uint32_t		getWidth()	const	{ return _width; }
	uint32_t		getHeight()	const	{ return _height; }
	SDL_Texture*	getData() const		{ return _texture; }

private:
	uint32_t		_width;			
	uint32_t		_height;
	SDL_Texture*	_texture;
};


typedef std::shared_ptr< Texture >	TexturePtr;