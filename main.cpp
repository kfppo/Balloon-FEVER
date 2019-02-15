#include <iostream>
#include "globals.h"
#include "texture.h"
#include "classes.h"
using namespace std;

int main(int argc, char* args[])
{
	//SDL Initialization
    if (!init())
    {
        cout << "Initialize SDL subsystem failed!" << endl;
    }
    else
    {
	//Load media
        if (!loadMedia())
        {
            cout << "Load media files failed!" << endl;
        }
        else
        {
	    //Start from intro state
            stateID = STATE_INTRO;
            currentState = new Intro();

	    //Balloon giver start from standing state
            currentAction = &standingState;

	    //Add a kitty before start
            kittyList.push_back(new Kitty());

	    //Run the state
            while (stateID != STATE_EXIT)
            {
                currentState->handle_events();
                currentState->logic();
                change_state();
                currentState->render();
            }
        }
    }
    close();
    return 0;
}
