#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED
#include <SDL.h>
#include "texture.h"

//Game states enum
enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    STATE_PLAY,
    STATE_EXIT
};

//Game state base class
class GameState
{
public:
    virtual void handle_events(){};
    virtual void logic(){};
    virtual void render(){};
	bool GAMEOVER;
};

class Intro : public GameState
{
public:
    Intro();
    ~Intro();
    void handle_events();
    void logic();
    void render();

private:
	LTexture* background;
	bool is_read;
	int scoresHistory;
};

class Title : public GameState
{
public:
    Title();
    ~Title();
    void handle_events();
    void logic();
    void render();

private:
	LTexture* background;
};

class Play : public GameState
{
public:
    Play();
    ~Play();
    void handle_events();
    void logic();
    void render();
	
private:
	bool is_SpriteStop;
	Uint32 waitTime;
	LTexture* background;
};

//Giver state base class
class SpriteAction
{
public:
    virtual void handleInput(SDL_Event& e) {}
    virtual void update() {}
};

//Sprite base class
class Sprite
{
public:
    Sprite();
    virtual void handle_input(SDL_Event &e) {}
    virtual void move() {}
    virtual void render() {}

private:
    //Sprite's current action state variable
    float mPosX, mPosY;
    float mVelX, mVelY;
};

class Giver : public Sprite
{
public:
    Giver();
    void handle_input(SDL_Event& e);
    void render();
	void setBallType(int ballType);
	int getBallType();
	bool checkLinked();
	float getPosX();
	bool alive;

private:
    float mPosX, mPosY;
    float mVelX, mVelY;
};

class Kitty : public Sprite
{
public:
    Kitty();
	static const int SPRITE_WIDTH = 160;
	static const int SPRITE_HEIGHT = 250;
    void handle_input(SDL_Event& e);
    void move();
    void render();
    void update();
    bool outScreen();
    void setWalkSpeed();
    void stopKitty();
    bool distForNewKitty(float dist);
	bool takeBallPosX();
	int getPosX();
	int getPosY();
	bool checkTaken();		//Check if kitty get the balloon
	void setTaken(bool taken);
private:
    float mPosX, mPosY;
    float mVelX, mVelY;
    int kittySize;
    bool ballTaken;
};

class Balloon : public Sprite
{
	friend class Giver;
public:
	Balloon();
	void move();
	void render();
	bool outScreen();
	void initSize(int size);
	void linkKitty(Kitty*);
	Kitty* linkKitty();

private:
	//Sprite's current action state variable
	float mPosX, mPosY;
	Kitty* taker;
	int ballType;
};

class GivingState : public SpriteAction
{
    friend class StandingState;
public:
    void handleInput(SDL_Event &e);
    void update();
};

class StandingState : public SpriteAction
{
public:
    void handleInput(SDL_Event &e);
    void update();
};
#endif // CLASSES_H_INCLUDED
