#include "Texture.h"

Texture::Texture( uint32_t inWidth, uint32_t inHeight, SDL_Texture* inTexture ) :
	_width( inWidth ),
	_height( inHeight ),
	_texture( inTexture )
{}

Texture::~Texture()
{
	SDL_DestroyTexture( _texture );
}