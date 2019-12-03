# Object
OBJS = main.cpp classes.h globals.h texture.h globals.cpp init.cpp sprites.cpp states.cpp texture.cpp

# Object name
OBJ_NAME = balloon

all : $(OBJS)
	g++ $(OBJS) -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o $(OBJ_NAME)
