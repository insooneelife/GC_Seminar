#include "Texture.h"

Texture::Texture(int width, int height, SDL_Texture* texture)
	:
	_width(width),
	_height(height),
	_texture(texture)
{}

Texture::~Texture()
{
	SDL_DestroyTexture(_texture);;
}