# Balloon-FEVER
A 2D balloon-giving game written in C++ and SDL2 libraries

<img src="resources/preview.PNG" width="600px" height="479px"></img>

#### Gameplay video:
[https://youtu.be/oTC2I40KMhE](https://youtu.be/oTC2I40KMhE)

## Instructions
To build this project, you will need to install SDL2 developer libraries:

[SDL2](https://www.libsdl.org/download-2.0.php)<br/>
[SDL2_image](https://www.libsdl.org/projects/SDL_image/)<br/>
[SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)<br/>
[SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)<br/>

#### For Linux, you can install the required libraries in one line:
`sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`<br/>
#### Compile the source using the make command: 
`make all`<br/>
#### Run the game: 
`./balloon`

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
