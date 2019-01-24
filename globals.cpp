#include "globals.h"
#include "texture.h"
#include "classes.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event event;
TTF_Font *font = NULL;
Mix_Music *gMusic = NULL;
Mix_Chunk *gTakeBalloon = NULL;
Mix_Chunk *gGiveBalloon = NULL;

GameState* currentState = NULL;
SpriteAction* currentAction = NULL;

Giver myGiver;
Kitty* currentKitty;
Balloon* currentBalloon;

StandingState standingState;
GivingState givingState;

LTexture gBGTexture;
LTexture gSpriteTexture;
LTexture gBG2Texture;
LTexture gBG3Texture;
LTexture gSpriteSheetTexture;
LTexture gTextTexture;
LTexture gTextScoreTexture;
SDL_Rect gSpriteClips[FRAME_TOTAL];
SDL_Rect* currentClip = 0;
SDL_Rect* currentClip2 = 0;
SDL_Rect* currentGiverClip = 0;

std::vector<Kitty*> kittyList = {};
std::vector<Balloon*> balloonList = {};

SDL_Color textColor = { 80, 80, 80 };

int stateID = STATE_NULL;
int nextState = STATE_NULL;
int frame = 0;
int scores = 0;

//Control kitty's walking speed. Default = -1.5f
float newSpeed = -1.5f;