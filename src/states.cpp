#include "classes.h"
#include "globals.h"
#include <iostream>
#include "SDL_mixer.h"
#include <fstream>

Intro::Intro()
{
	scoresHistory = 0;
	is_read = false;
	background = &gBGTexture;
}

Intro::~Intro()
{
	//Blank
}

void Intro::handle_events()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			set_next_state(STATE_EXIT);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			Mix_PlayChannel(-1, gGiveBalloon, 0);
			set_next_state(STATE_TITLE);
		}
	}
}

void Intro::logic()
{
	//Load saved game
	if (is_read)
	{
		//Do nothing
	}
	else
	{
		scoresHistory = readSaved();
		std::cout << "The Highest Score: ";
		std::cout << scoresHistory << std::endl;
		is_read = true;

		//Load text texture
		if (!gTextScoreTexture.loadFromRenderedText(std::to_string(scoresHistory), textColor))
		{
			std::cout << "Failed to load Score history text texture!" << std::endl;
		}
	}
}

void Intro::render()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	background->render(0, 0);
	gTextScoreTexture.render((SCREEN_WIDTH - gTextScoreTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextScoreTexture.getHeight()) / 2);
	SDL_RenderPresent(gRenderer);
}

Title::Title()
{
	background = &gBG2Texture;
}

Title::~Title()
{
	//Blank
}

void Title::handle_events()
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			set_next_state(STATE_EXIT);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			Mix_PlayChannel(-1, gGiveBalloon, 0);
			set_next_state(STATE_PLAY);
		}
	}
}

void Title::logic()
{
	//Blank
}

void Title::render()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	background->render(0, 0);
	SDL_RenderPresent(gRenderer);
}

Play::Play()
{
	GAMEOVER = false;
	is_SpriteStop = false;
	waitTime = 0;
	background = &gBG3Texture;
}

Play::~Play()
{
	//blank
}

void Play::handle_events()
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			set_next_state(STATE_EXIT);
		}
		myGiver.handle_input(event);
	}
}

void Play::logic()
{
	if (!GAMEOVER)
	{
		//Incrase the kitty walking speed a little bit each frame
		newSpeed -= speedGradient;
		currentKitty = kittyList[kittyList.size() - 1];

		//Create a new kitty if the previous one walk a specific distant  
		if (currentKitty->distForNewKitty(distForNewKitty))
		{
			kittyList.push_back(new Kitty());
		}

		//Delete kitty if walk outside of screen
		currentKitty = kittyList[0];
		if (currentKitty->outScreen())
		{
			delete currentKitty;
			kittyList.erase(kittyList.begin());

			//Delete balloon if taker walk outside of screen
			if (balloonList.size() != 0)
			{
				currentBalloon = balloonList[0];
				delete currentBalloon;
				balloonList.erase(balloonList.begin());
			}
		}

		//Show the score
		if (!gTextTexture.loadFromRenderedText(std::to_string(scores), textColor))
		{
			std::cout << "failed to load scores!" << std::endl;
		}

		//Play the music
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}
	}
	else
	{
		//If sprite haven't stopped
		if (!is_SpriteStop)
		{
			//Stop all sprites
			for (int i = 0; i < kittyList.size(); ++i)
			{
				kittyList[i]->stopKitty();
				kittyList[i]->setTaken(true);
			}

			//Stop music
			Mix_HaltMusic();
			waitTime = SDL_GetTicks();
			is_SpriteStop = true;

			//Write score to file
			writeSaved();
		}
		//If sprite was stopped
		else
		{
			//Wait 2 secondsd and play game over scene
			if ((SDL_GetTicks() - waitTime) > 2000 && (SDL_GetTicks() - waitTime) < 4000)
			{
				if (myGiver.alive == true)
				{
					Mix_PlayChannel(-1, gTakeBalloon, 0);
					myGiver.alive = !currentState->GAMEOVER;
				}
			}
			//After game over scene, go back to Intro state
			else if ((SDL_GetTicks() - waitTime) > 4000 && (SDL_GetTicks() - waitTime) < 7000)
			{
				set_next_state(STATE_INTRO);
				initWorld();
			}
		}
	}
}

void Play::render()
{
	currentAction->update();
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	background->render(0, 0);
	myGiver.render();
	gTextTexture.render(SCREEN_WIDTH - (gTextTexture.getWidth() + 30), 10);

	//Kitty movement
	for (int it = 0; it < kittyList.size(); ++it)
	{
		currentKitty = kittyList[it];
		currentKitty->move();
		currentKitty->setWalkSpeed();
		currentKitty->update();
		currentKitty->render();
	}

	//Balloon movement
	for (int it = 0; it < balloonList.size(); ++it)
	{
		currentBalloon = balloonList[it];
		currentBalloon->move();
		currentBalloon->render();
	}

	SDL_RenderPresent(gRenderer);

	if (!GAMEOVER)
	{
		++frame;
	}
	if (frame / 10 >= SMALL_WALKING_FRAMES) frame = 0;
}

//The state of giver with no balloon in hand
void StandingState::handleInput(SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			//Change action state to giving state
			currentAction = &givingState;

			//Create a new balloon
			balloonList.push_back(new Balloon());

			//Set the giving balloon type
			myGiver.setBallType(1);
			
			//Initialize small balloon position
			balloonList[balloonList.size() - 1]->initSize(1);

			//Play the balloon giving sound
			Mix_PlayChannel(-1, gGiveBalloon, 0);
		}
		else if (e.button.button == SDL_BUTTON_RIGHT)
		{
			//Change action state to giving state
			currentAction = &givingState;

			balloonList.push_back(new Balloon());
			myGiver.setBallType(2);

			//Initialize big balloon position
			balloonList[balloonList.size() - 1]->initSize(2);

			Mix_PlayChannel(-1, gGiveBalloon, 0);
		}
	}
}

//The state of giver with balloon in hand
void GivingState::handleInput(SDL_Event& e)
{
	//Do nothing
}

void StandingState::update()
{
	//Do nothing
}

void GivingState::update()
{
	if (!currentState->GAMEOVER)
	{
		//If a kitty get the balloon
		if (myGiver.checkLinked())
		{
			//Giver change back to standing state
			currentAction = &standingState;

			//Play the balloon taking sound
			Mix_PlayChannel(-1, gTakeBalloon, 0);

			//Add 1 point
			if (!gTextTexture.loadFromRenderedText(std::to_string(scores++), textColor))
			{
				std::cout << "Failed to load scores!" << std::endl;
			}
		}
	}
}

//Set the next state
void set_next_state(int newState)
{
	if (nextState != STATE_EXIT)
	{
		nextState = newState;
	}
}

//Change the state
void change_state()
{
	if (nextState != STATE_NULL)
	{
		if (nextState != STATE_EXIT)
		{
			delete currentState;
		}

		switch (nextState)
		{
		case STATE_TITLE:
			currentState = new Title();
			break;
		case STATE_PLAY:
			currentState = new Play();
			break;
		case STATE_INTRO:
			currentState = new Intro();
			break;
		}
		stateID = nextState;
		nextState = STATE_NULL;
	}
}

//Initialize everything
void initWorld()
{
	newSpeed = -1.5f;
	currentClip = 0;
	currentClip2 = 0;
	currentGiverClip = 0;
	currentBalloon = 0;
	currentKitty = 0;
	kittyList.clear();
	balloonList.clear();
	kittyList.push_back(new Kitty());
	currentAction = &standingState;
	frame = 0;
	scores = 0;
	myGiver.alive = true;
}

//Read the saved game
int readSaved()
{
	std::ifstream save("saved.bin", std::ios::binary);
	if (!save.is_open())
	{
		std::cout << "Saved game not found. New saved game created!" << std::endl;
		std::ofstream save("saved.bin", std::ios::binary);
		int highestScore = 0;
		save.write((char*)(&highestScore), sizeof(highestScore));
		return highestScore;
	}
	else
	{
		int readScore = 0;
		save.read((char*)(&readScore), sizeof(int));
		return readScore;
	}
}

//Write save game
void writeSaved()
{
	std::ifstream save("saved.bin", std::ios::binary);
	if (save.is_open())
	{
		int readScore = 0;
		save.read((char*)(&readScore), sizeof(int));

		if (scores > readScore)
		{
			std::cout << "NEW RECORD!" << std::endl;
			std::ofstream save("saved.bin", std::ios::binary);
			save.write((char*)(&scores), sizeof(int));
		}
		else
		{
			std::cout << "Not the highest score!" << std::endl;
		}
	}
}

