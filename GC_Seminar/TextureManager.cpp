#include "TextureManager.h"
#include "GraphicsDriver.h"
#include <sstream>
#include <iomanip>
#include <string>
#include <SDL\SDL_image.h>


std::unique_ptr< TextureManager >		TextureManager::instance = nullptr;

void TextureManager::StaticInit()
{
	instance.reset( new TextureManager() );
}

TextureManager::TextureManager()
{
	cacheTexture( "cat", "../Assets/cat.png" );
}

TexturePtr	TextureManager::GetTexture( const std::string& inTextureName )
{
	return _name_to_text_map[ inTextureName ];
}


bool TextureManager::cacheTexture( std::string inTextureName, const char* inFileName )
{
	SDL_Texture* texture = IMG_LoadTexture( GraphicsDriver::instance->getRenderer(), inFileName );

	if( texture == nullptr )
	{
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed to load texture: %s", inFileName );
		return false;
	}

	int w, h;
	SDL_QueryTexture( texture, nullptr, nullptr, &w, &h );

	// Set the blend mode up so we can apply our colors
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	
	TexturePtr newTexture( new Texture( w, h, texture ) );

	_name_to_text_map[ inTextureName ] = newTexture;

	return true;
}