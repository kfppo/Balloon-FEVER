#include <SDL.h>
#include <iostream>
#include "globals.h"

//Initialize SDL subsystems
bool init()
{
	bool success = true;

	SDL_Init(SDL_INIT_EVERYTHING);

	//Create window for the game
	gWindow = SDL_CreateWindow("Balloon FEVER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Create renderer for the window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (gRenderer == NULL)
		{
			std::cout << SDL_GetError()	<< std::endl;
			success = false;
		}
		else
		{
			//Initialize the render draw color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize SDL image subsystem
			int imgFlag = IMG_INIT_PNG;
			if (IMG_Init(imgFlag) != imgFlag)
			{
				std::cout << IMG_GetError() << std::endl;
				success = false;
			}

			//Initialize SDL mixer
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
			{
				std::cout << Mix_GetError() << std::endl;
				success = false;
			}

			//Initialize SDL TTF
			if (TTF_Init() == -1)
			{
				std::cout << TTF_GetError() << std::endl;
				success = false;
			}
		}
	}
	return success;
}

//Load game media files
bool loadMedia()
{
	bool success = true;

	if (!gBGTexture.loadFromFile("resources/bg_intro.png"))
	{
		std::cout << IMG_GetError() << std::endl;
		success = false;
	}
	if (!gBG2Texture.loadFromFile("resources/bg_title.png"))
	{
		std::cout << IMG_GetError() << std::endl;
		success = false;
	}
	if (!gBG3Texture.loadFromFile("resources/bg_play.png"))
	{
		std::cout << IMG_GetError() << std::endl;
		success = false;
	}
	if (!gSpriteSheetTexture.loadFromFile("resources/sheet.png"))
	{
		std::cout << IMG_GetError() << std::endl;
		success = false;
	}

	//Load sound & music files
	gMusic = Mix_LoadMUS("resources/bg_music.mp3");
	if (gMusic == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
		success = false;
	}
	gTakeBalloon = Mix_LoadWAV("resources/take.wav");
	if (gTakeBalloon == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
		success = false;
	}
	gGiveBalloon = Mix_LoadWAV("resources/give.wav");
	if (gGiveBalloon == NULL)
	{
		std::cout << Mix_GetError() << std::endl;
		success = false;
	}

	//Load font file
	font = TTF_OpenFont("resources/OpenSans-Bold.ttf", 70);
	if (font == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
	}


	//Sheet table index:
	//0-9: Small kitty walking
	//10-19: Small kitty taking
	//20-29: Big kitty walking
	//30-39: Big kitty taking
	//40: Balloon giver giving
	//41: Balloon giver idle
	//42: big balloon
	//43: small balloon
	//44: giver game over

	//Small kitty walking
	for (int i = 5, n = 0; n < 10; ++n, i += 168)
	{
		gSpriteClips[n].x = i;
		gSpriteClips[n].y = 355;
		gSpriteClips[n].w = 170;
		gSpriteClips[n].h = 353;
	}

	//Small kitty taking
	for (int i = 0, n = 10; n < 20; ++n, i += 169)
	{
		gSpriteClips[n].x = i;
		gSpriteClips[n].y = 0;
		gSpriteClips[n].w = 168;
		gSpriteClips[n].h = 345;
	}

	//Big kitty walking
	for (int i = 0, n = 20; n < 30; ++n, i += 170)
	{
		gSpriteClips[n].x = i;
		gSpriteClips[n].y = 1710;
		gSpriteClips[n].w = 170;
		gSpriteClips[n].h = 345;
	}

	//Big kitty taking
	for (int i = 0, n = 30; n < 40; ++n, i += 169)
	{
		gSpriteClips[n].x = i;
		gSpriteClips[n].y = 1365;
		gSpriteClips[n].w = 168;
		gSpriteClips[n].h = 340;
	}

	//Balloon giver
	for (int i = 0, n = 40; n < 42; ++n, i += 168)
	{
		gSpriteClips[n].x = i;
		gSpriteClips[n].y = 715;
		gSpriteClips[n].w = 168;
		gSpriteClips[n].h = 260;
	}

	//Big balloon clips
	gSpriteClips[42].x = 75;
	gSpriteClips[42].y = 980;
	gSpriteClips[42].w = 145;
	gSpriteClips[42].h = 370;

	//Small balloon clips
	gSpriteClips[43].x = 0;
	gSpriteClips[43].y = 980;
	gSpriteClips[43].w = 76;
	gSpriteClips[43].h = 260;

	//Giver game over clip
	gSpriteClips[44].x = 345;
	gSpriteClips[44].y = 715;
	gSpriteClips[44].w = 210;
	gSpriteClips[44].h = 290;
	
	return success;
}

//Release memory
void close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	Mix_FreeMusic(gMusic);
	Mix_FreeChunk(gTakeBalloon);
	Mix_FreeChunk(gGiveBalloon);
	TTF_CloseFont(font);
	gBGTexture.free();
	gBG2Texture.free();
	gBG3Texture.free();
	gSpriteTexture.free();
	gTextTexture.free();
	gTextScoreTexture.free();
	gTakeBalloon = NULL;
	gGiveBalloon = NULL;
	gMusic = NULL;
	font = NULL;
	gRenderer = NULL;
	gWindow = NULL;

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}