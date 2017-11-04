CC = g++ #Compiler
CFLAGS = -w #Compilation Flags
LFLAGS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_gfx #Linking Flags

.DEFAULT_GOAL := build

DEPS = *.h #Headers

#SOURCE specifies the source code in plain text
SOURCE = *.cpp

#OBJS specifies which files are compiled as part of the project and ready to link
OBJS := $(SOURCE:.cpp=.o)

#EXE_NAME specifies the name of our exectuable
EXE_NAME = MagicDrawing

#Remove OBJS and EXE_NAME
clean :
	rm -f $(OBJS) $(EXE_NAME)

#Compile but not link the .cpps
compile : $(SOURCE) $(DEPS)
	$(CC) -c $(SOURCE) $(CFLAGS)

#Link the generated objects
link : compile
	$(CC) $(OBJS) $(LFLAGS) -o $(EXE_NAME)

#This is the target that compiles our executable
build : link
	
