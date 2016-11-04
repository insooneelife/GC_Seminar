#include <memory>
#include <string>
#include <unordered_map>

class Texture;
class TextureManager
{
public:
	static void StaticInit();

	static std::unique_ptr<TextureManager> sInstance;

	Texture* GetTexture(const std::string& texture_name);

private:
	TextureManager();

	bool CacheTexture(std::string name, const char* file_name);

	std::unordered_map<std::string, Texture*> _name_to_texture;
};