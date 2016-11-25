#include <SDL/SDL.h>
#include <memory>

class Texture
{
public:
	Texture(int width, int height, SDL_Texture* texture);
	~Texture();

	int	getWidth()	const			{ return _width; }
	int	getHeight()	const			{ return _height; }
	SDL_Texture* getData() const	{ return _texture; }

private:
	int _width;			
	int	_height;
	SDL_Texture* _texture;
};
