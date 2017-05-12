OBJS = 02_getting_an_image_on_the_screen.cpp
CC = g++
INCLUDE_FLAGS = -I	/usr/include/SDL2
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2
OBJ_NAME = 02_getting_an_image_on_the_screen
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
