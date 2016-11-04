#include <SDL/SDL.h>
#include <memory>

class Texture
{
public:
	Texture(int width, int height, SDL_Texture* texture);
	~Texture();

	int	GetWidth()	const			{ return _width; }
	int	GetHeight()	const			{ return _height; }
	SDL_Texture* GetData() const	{ return _texture; }

private:
	int _width;			
	int	_height;
	SDL_Texture* _texture;
};
