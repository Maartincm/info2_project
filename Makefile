#OBJS specifies which files to compile as part of the project
OBJS = sdl.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = proy1

#This is the target that compiles our executable
all : $(OBJS)
		g++ $(OBJS) -w -lSDL2 -lSDL2main -o $(OBJ_NAME)
