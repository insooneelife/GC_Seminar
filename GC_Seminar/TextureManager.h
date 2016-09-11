#include <memory>
#include <string>
#include <unordered_map>
#include "Texture.h"


class TextureManager
{
public:
	static void StaticInit();

	static std::unique_ptr< TextureManager >		instance;

	TexturePtr	GetTexture( const std::string& inTextureName );

private:
	TextureManager();

	bool cacheTexture( std::string inName, const char* inFileName );

	std::unordered_map< std::string, TexturePtr >	_name_to_text_map;
};