#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Texture handler class
class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile(std::string path);
	bool loadFromRenderedText(std::string text, SDL_Color textColor);
    void render(float x, float y, SDL_Rect* clip = NULL);
    void free();
	int getWidth();
	int getHeight();

private:
    SDL_Texture* mTexture;
    int mWidth, mHeight;
};

#endif // TEXTURE_H_INCLUDED
