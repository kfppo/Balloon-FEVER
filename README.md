## Balloon-FEVER
A cross-platform (Windows, Linux) 2D clicker game written in C++ and SDL2 libraries

<img src="/src/resources/preview.PNG" width="600px" height="479px"></img>

#### Gameplay video: [https://youtu.be/oTC2I40KMhE](https://youtu.be/oTC2I40KMhE)

### Setup

#### For Windows: (Tested on Windows 10 1909)
Requires: Visul Studio (tested on VS16 2019), SDL2 developer libraries, CMake

#### 1. Install SDL2 developer libraries:
(Make sure to download the Development Libraries with tag "Visual C++ 32/64-bit")<br>

[SDL2](https://www.libsdl.org/download-2.0.php)<br/> 
[SDL2_image](https://www.libsdl.org/projects/SDL_image/)<br/>
[SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)<br/>
[SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)<br/>

Unzip the 4 files above and copy all files inside</br>
`SDL2_mixer-x.x.x`, `SDL2_image-x.x.x`, `SDL2_ttf-x.x.x`, `SDL2_mixer-x.x.x` folder</br>
to: </br>
folder `Balloon-FEVER/src/lib`</br>
(Choose "Replace" if Replace or Skip Files dialog show up while copying)

#### 2. Install CMake
Download [CMake](https://cmake.org/download/)
(Windows win32-x86 Installer)</br>
</br>
(Make sure to Check "Add CMake to the system PATH for all users" during the installation. This allows you to fire CMake command in PowerShell window)</br>

#### 3. Build the project
Open PoweShell window and direct to `Balloon-FEVER/build`</br>
</br>
Run `cmake ../src` to build the project.

#### 4. Copy all required .dll files to `Balloon-FEVER/build` folder
For Windows x64, the required .dll files are in `Balloon-FEVER/src/lib/lib/x64`</br>
For Windows x86, the required .dll files are in `Balloon-FEVER/src/lib/lib/x86`</br>

#### 5. Use Visual Studio to open the project `balloon.sln` in `Balloon-FEVER/build` folder
#### 6. Open Solution Explorer inside Visual Studio, right click on "balloon" project and "Set as StartUp Project"
#### 7. Compile and Run
---
#### For Linux: (Tested on Ubuntu 18.04 LTS)
Requires: SDL2 developer libraries, CMake, make

#### 1. Install the required libraries
Linux user can install the required libraries in one command line:</br>
`sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev cmake make`

#### 2. Build the project
Open Terminal and dirrect to `Balloon-FEVER/build`</br>
</br>
Run `cmake ../src` to build the project

#### 3. Run `make` to compile the project
#### 4. Run `./balloon` to start the program

### Game Control
- Left mouse button: Give small balloon
- Right mouse button: Give big balloon

### Credits
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
