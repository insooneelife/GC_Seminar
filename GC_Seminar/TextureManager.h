#include <memory>
#include <string>
#include <unordered_map>

class Texture;
class TextureManager
{
public:
	static void staticInit();

	static std::unique_ptr<TextureManager> instance;

	const Texture& getTexture(const std::string& texture_name);

private:
	TextureManager();

	bool cacheTexture(std::string name, const char* file_name);

	std::unordered_map<std::string, std::unique_ptr<Texture>> _name_to_texture;
};