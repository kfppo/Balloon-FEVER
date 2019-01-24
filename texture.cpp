#include <iostream>
#include "texture.h"
#include "globals.h"

//Initialize variables
LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

//Free memory
LTexture::~LTexture()
{
    free();
}

//Load image
bool LTexture::loadFromFile(std::string path)
{
    free();
    SDL_Texture* finalTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
       std::cout << SDL_GetError() << std::endl;
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        finalTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (finalTexture == NULL)
        {
            std::cout << SDL_GetError() << std::endl;
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        mTexture = finalTexture;
        SDL_FreeSurface(loadedSurface);
    }
    return mTexture != NULL;
}

//Load text
bool LTexture::loadFromRenderedText(std::string text, SDL_Color textColor)
{
	free();
	SDL_Texture* finalTexture = NULL;
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	if (loadedSurface == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
	}
	else
	{
		finalTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (finalTexture == NULL)
		{
			std::cout << SDL_GetError() << std::endl;
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		mTexture = finalTexture;
		SDL_FreeSurface(loadedSurface);
	}
	return mTexture != NULL;
}

//Render the texture
void LTexture::render(float x, float y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

//Free memory
void LTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

//Get width of texture
int LTexture::getWidth()
{
	return mWidth;
}

//Get height of texture
int LTexture::getHeight()
{
	return mHeight;
}