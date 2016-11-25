#include <SDL/SDL_image.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "GraphicsDriver.h"
#include "Texture.h"

using namespace std;

std::unique_ptr<TextureManager> TextureManager::instance = nullptr;


void TextureManager::staticInit()
{
	instance.reset(new TextureManager());
}

TextureManager::TextureManager()
{
	cacheTexture("cat", "cat.png");

	string actions[4] =
	{
		"Idle", "Move", "Attack", "Death"
	};
	
	for(auto action : actions)
	{
		for (int i = 1; i <= 45; i++)
		{
			stringstream image_number, cache_number;
			image_number << std::setfill('0') << std::setw(2) << i;
			cache_number << i - 1;
			cacheTexture(
				"Zealot" + action + cache_number.str(),
				("../Assets/Zealot/" + action + "/_" + image_number.str() + ".png").c_str());
		}
	}
}

const Texture& TextureManager::getTexture(const string& texture_name)
{
	return *_name_to_texture[texture_name];
}


bool TextureManager::cacheTexture(string texture_name, const char* file_name)
{
	std::cout << file_name << std::endl;
	SDL_Texture* texture = IMG_LoadTexture(GraphicsDriver::instance->getRenderer(), file_name);

	if( texture == nullptr )
	{
		std::cout << "fail" << endl;;
		SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Failed to load texture: %s", file_name);
		return false;
	}

	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	// Set the blend mode up so we can apply our colors
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	
	_name_to_texture.emplace(texture_name, new Texture(w, h, texture));

	return true;
}