#include "classes.h"
#include "globals.h"
#include <time.h>
#include <random>
#include <iostream>

//Initialize a Mersenne Twister pseudo-random generator
std::mt19937 gen(time(NULL));
//Produce random integer values
std::uniform_int_distribution<int> randKittySize(1, 2);
std::uniform_int_distribution<int> pos(-1, 1);

//Initialize Sprite class variables
Sprite::Sprite()
{
	mPosX = SCREEN_WIDTH / 2;
	mPosY = SCREEN_HEIGHT / 2;
	mVelX = 0;
	mVelY = 0;
}

//Initialize Giver class variables
Giver::Giver()
{
	mPosX = 30;
	mPosY = 180;
	mVelX = 0;
	mVelY = 0;
	alive = true;
}

void Giver::handle_input(SDL_Event& e)
{
	currentAction->handleInput(e);
}

void Giver::render()
{
	if (alive)
	{
		if (checkLinked())
		{
			//Render balloon giver with no balloon posture
			currentGiverClip = &gSpriteClips[41];
			gSpriteSheetTexture.render(mPosX, mPosY, currentGiverClip);
		}
		else
		{
			//Render balloon Giver with balloon posture
			currentGiverClip = &gSpriteClips[40];
			gSpriteSheetTexture.render(mPosX, mPosY, currentGiverClip);
		}
	}
	else
	{
		//Render balloon giver sad posture
		currentGiverClip = &gSpriteClips[44];
		gSpriteSheetTexture.render(mPosX, mPosY, currentGiverClip);		
	}
}

//Set the giving balloon type
void Giver::setBallType(int ballType)
{
	if (balloonList.size())
	{
		balloonList[balloonList.size() - 1]->ballType = ballType;
	}
	else
	{
		//std::cout << "WARNING: ballonList is empty, cannot set ballType" << std::endl;
	}
}

//Get the giver position x
float Giver::getPosX()
{
	return mPosX;
}

//Get the giving balloon type
int Giver::getBallType()
{
	if (balloonList.size())
	{
		return balloonList[balloonList.size() - 1]->ballType;
	}
	else
	{
		//std::cout << "WARNING: balloonList is empty, return ballType = 0" << std::endl;
		return 0;
	}
	
}

//Check if the current balloon was picked by a kitty
bool Giver::checkLinked()
{
	if (balloonList.size())
	{
		if (balloonList[balloonList.size() - 1]->linkKitty() != NULL)
			return 1;
		else
			return 0;
	}
	else
		return 1;
}

//Initialize Kitty class variables
Kitty::Kitty()
{
	mPosX = SCREEN_WIDTH;
	mPosY = 100;
	mVelX = -3;

	mVelY = 0;// + pos(gen);
	//random pick 1 or 2
	kittySize = randKittySize(gen);
	ballTaken = false;
}

void Kitty::handle_input(SDL_Event& e)
{
	//Kitty don't need to handle input
}

//Move the kitty
void Kitty::move()
{
	mPosX += mVelX;
	mPosY += mVelY;
}

void Kitty::render()
{
	//If the kitty is a big kitty
	if (kittySize == 2)
	{
		//If the kitty is in taking balloon area
		if (!takeBallPosX())
		{
			//Render big kitty walking clips
			currentClip = &gSpriteClips[(frame / 10) + 20];
			gSpriteSheetTexture.render(mPosX, mPosY, currentClip);
		}
		else
		{
			//Render big kitty taking clips
			currentClip = &gSpriteClips[(frame / 10) + 30];
			gSpriteSheetTexture.render(mPosX, mPosY, currentClip);
		}
	}
	else
	{
		if (!takeBallPosX())
		{
			//Render small kitty walking clips
			currentClip = &gSpriteClips[frame / 10];
			gSpriteSheetTexture.render(mPosX, mPosY, currentClip);
		}
		else
		{
			//Render small kitty taking clips
			currentClip = &gSpriteClips[(frame / 10) + 10];
			gSpriteSheetTexture.render(mPosX, mPosY, currentClip);
		}
	}
}

void Kitty::update()
{
	if (!ballTaken)
	{
		//If the kitty is in taking area
		if (mPosX < SPRITE_WIDTH)
		{
			//If the balloon match the kitty size
			if (myGiver.getBallType() == kittySize)
			{
				//Set kitty leaving speed
				mVelX = -15;
				mVelY = 15;
				ballTaken = true;
				balloonList[balloonList.size() - 1]->linkKitty(this);
			}
			else
			{
				//Wrong Balloon for kitty, Game Over Man, GAME OVER
				currentState->GAMEOVER = true;

				//Just to make sure giver won't be able to give balloon anymore
				currentAction = &givingState;
			}
		}
	}
}

//Check if kitty walk outside the screen
bool Kitty::outScreen()
{
	return mPosY > SCREEN_HEIGHT + 200;
}

//Set kitty walking speed
void Kitty::setWalkSpeed()
{
	if (!ballTaken)
	{
		mVelX = newSpeed;
	}
}

//Set kitty if get the balloon
void Kitty::setTaken(bool taken)
{
	if (taken)
		ballTaken = true;
	else
		ballTaken = false;
}

int Kitty::getPosX()
{
	return mPosX;
}

int Kitty::getPosY()
{
	return mPosY;
}

//Stop all kitty
void Kitty::stopKitty()
{
	mVelX = 0;
	mVelY = 0;
}

//Check if the previous kitty was walking a specific distant
bool Kitty::distForNewKitty(float dist)
{
	if (mPosX < SCREEN_WIDTH * dist)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Check if kitty get the balloon
bool Kitty::checkTaken()
{
	return ballTaken;
}

//The distant that kitty can get the balloon
bool Kitty::takeBallPosX()
{
	if (mPosX < myGiver.getPosX() + SPRITE_WIDTH)
		return 1;
	else
		return 0;
}

Balloon::Balloon()
{
	mPosX = 0;
	mPosY = 0;
	taker = 0;

	ballType = 0;
}

bool Balloon::outScreen()
{
	return mPosY > SCREEN_HEIGHT;
}

void Balloon::move()
{
	//If balloon have taker, follow the taker
	if (taker != NULL)
	{
		//std::cout << "have taker" << std::endl;
		mPosX = taker->getPosX() - 40;
		mPosY = taker->getPosY() - 20;
	}
}

void Balloon::render()
{
	//Render small balloon
	if (ballType == 1)
	{
		currentClip2 = &gSpriteClips[43];
		gSpriteSheetTexture.render(mPosX, mPosY, currentClip2);
	}

	//Render big balloon
	else if (ballType == 2)
	{
		currentClip2 = &gSpriteClips[42];
		gSpriteSheetTexture.render(mPosX, mPosY, currentClip2);
	}
	else
	{
		//std::cout << "Balloon type is not clear!" << std::endl;
	}
}

void Balloon::initSize(int size)
{
	//Initialize position for small balloon
	if (size == 1)
	{
		mPosX = 140;
		mPosY = 105;
	}
	//Initialize position for big balloon
	else if (size == 2)
	{
		mPosX = 113;
		mPosY = 5;
	}
	else
	{
		//std::cout << "Error: Wrong initSize argument input!" << std::endl;
	}
}

//Set taker if balloon have taker
void Balloon::linkKitty(Kitty* getKitty)
{
	taker = getKitty;
}

//Return balloon taker
Kitty* Balloon::linkKitty()
{
	return taker;
}