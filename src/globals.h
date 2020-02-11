#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include "classes.h"
#include "texture.h"
#include <vector>
#include <random>
#include "SDL_ttf.h"
#include "SDL_mixer.h"

//Screen Size
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Sprites animation
const int BIG_WALKING_FRAMES = 10;
const int SMALL_WALKING_FRAMES = 10;
const int BIG_TAKING_FRAMES = 10;
const int SMALL_TAKING_FRAMES = 10;
const int GIVER_FRAMES = 2;
const int BALLOON_FRAMES = 2;
const int GAMEOVER_FRAMES = 1;
const int FRAME_TOTAL = BIG_WALKING_FRAMES + SMALL_WALKING_FRAMES + BIG_TAKING_FRAMES + SMALL_TAKING_FRAMES + GIVER_FRAMES + BALLOON_FRAMES + GAMEOVER_FRAMES;

extern Mix_Music *gMusic;
extern Mix_Chunk *gTakeBalloon;
extern Mix_Chunk *gGiveBalloon;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font *font;
extern SDL_Event event;

extern GameState* currentState;
extern SpriteAction* currentAction;

//Texture handler
extern LTexture gBGTexture;
extern LTexture gSpriteTexture;
extern LTexture gBG2Texture;
extern LTexture gBG3Texture;
extern LTexture gSpriteSheetTexture;
extern LTexture gTextTexture;
extern LTexture gTextScoreTexture;
extern SDL_Rect gSpriteClips[FRAME_TOTAL];
extern SDL_Color textColor;
extern StandingState standingState;
extern GivingState givingState;
extern Kitty* currentKitty;
extern Balloon* currentBalloon;
extern SDL_Rect* currentClip;
extern SDL_Rect* currentClip2;
extern SDL_Rect* currentGiverClip;
extern Giver myGiver;

//Containers of kitty and balloon
extern std::vector<Kitty*> kittyList;
extern std::vector<Balloon*> balloonList;

//Initialize SDL subsystems
bool init();

//Load media files
bool loadMedia();

//Free memory
void close();

//State changer
void set_next_state(int newState);
void change_state();

//Initialize everything
void initWorld();

//Load scores from file
int readSaved();

//Write scores to file
void writeSaved();

//State variables
extern int stateID;
extern int nextState;

extern int scores;
extern int frame;

//The ratio of creating new kitty
const float distForNewKitty = 0.75f;

//Time constant (kitty walking speed according to the time)
const float timeGradient = 0.4f;
const float speedGradient = 0.002f;

extern float newSpeed;
#endif // GLOBALS_H_INCLUDED
