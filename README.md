## Balloon-FEVER
A cross-platform (Windows, Linux) 2D clicker game written in C++ and SDL2 libraries

<img src="/src/resources/preview.PNG" width="600px" height="479px"></img>

#### Demo video: [https://youtu.be/oTC2I40KMhE](https://youtu.be/oTC2I40KMhE)

## Setup

#### Windows (Tested on Windows 10 1909)
What You Need:<br>
- Visul Studio (tested on VS16 2019)
- SDL2 developer libraries ([SDL2](https://www.libsdl.org/download-2.0.php), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/), [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/))
- [CMake](https://cmake.org/download/) (Windows win32-x86 Installer)

##### Section 1 - Prep Work
1. Install SDL2 developer libraries:
    - Copy all files in the `SDL2-x.x.x`, `SDL2_image-x.x.x`, `SDL2_ttf-x.x.x` and `SDL2_mixer-x.x.x` to the `Balloon-FEVER/src/lib` folder
    - If you are prompted to handle duplicate files, press Replace
2. Install CMake
    - Make sure to Check "Add CMake to the system PATH for all users" in installation menu

##### Section 2 - Build and Run
1. Open PoweShell window and navigate to the `Balloon-FEVER/build` folder
2. Invoke command `cmake ../src` in Powershell to build the project
3. Copy required .dll files to the `Balloon-FEVER/build` folder
    - For Windows x64 user, the required .dll files are in the `Balloon-FEVER/src/lib/lib/x64` folder
    - For Windows x86 user, the required .dll files are in the `Balloon-FEVER/src/lib/lib/x86` folder
4. Open the project `balloon.sln` in the 'Balloon-FEVER/build' folder using Visual Studio
5. Open Solution Explorer in the right side of the Visual Studio panel
6. Right click on project "balloon" and select "Set as StartUp Project"
7. Compile and Run (or press F5)

---
#### Linux (Tested on Ubuntu 18.04 LTS)
What You Need: (See Section 1 for installation)<br>
- SDL2 developer libraries
- CMake
- make

##### Section 1 - Prep Work
1. Install the required libraries
    - Invoke command `sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev cmake make` in the terminal

##### Section 2 - Build and Run
1. Open Terminal and navigate to the `Balloon-FEVER/build` folder
2. Invoke command `cmake ../src` to build the project
3. Invoke command `make` to compile the project
4. Invoke command `./balloon` to start the game

## Game Control
- Left mouse button: Give small balloon
- Right mouse button: Give big balloon

## Credits
 - Some of the code in this project is repurposed from [Lazy Foo's tutorials](http://lazyfoo.net/tutorials/SDL/index.php).
 - Background music (resources/bg_music.mp3)
<br>"Salty Ditty" by Kevin MacLeod (https://incompetech.com)
<br>Licence: CC BY (http://creativecommons.org/licenses/by/4.0/)
 - Balloon taking sound (resources/take.wav)
 <br>"Waterdrop" by Porphyr (https://freesound.org)
 <br>Licence: CC BY (http://creativecommons.org/licenses/by/3.0/)
 - Score board font (resources/OpenSans-Bold.ttf): 
<br>"OpenSans-Bold" by Ascender Fonts (http://www.ascenderfonts.com) 
<br>Licence: Apache License v2.00 (https://www.fontsquirrel.com/license/open-sans)
