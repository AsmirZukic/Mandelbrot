#The name of the binary we will be creating 
BINARY=bin 
#directories with all our source (.cpp) files 
CODEDIR=. src
#Directories with all our header (.hpp) files 
INCDIR=. /include/

#Compiler. Define as gcc for C and g++ for C++
CC=g++ 

#Optimization flag
# -O0 no optimization, faster compile time, great for debugging builds
OPT=-O0

#Generate files that encode make rules for .hpp dependencies 
DEPFLAGS=-MP -MD

#Compiler flags
# -Wall used to turn on most warnings
# -c compiles sources to object files 
# For each loop used to add -I onto each include directory
CFLAGS=-c -Wall -g $( foreach D, $(INCDIR), -I$(D) ) $(OPT) $(DEPFLAGS)

#SDL2 comipler flasgs 
SDL2=-w -lSDL2 -lSDL2_image

#Regular expression to find all the source files inside the source directories
SOURCE=$(foreach D, $(CODEDIR), $(wildcard $(D)/*.cpp) )

#Regular expression replacement 
OBJECT= $(patsubst %.cpp, %.o, $(SOURCE) )
DEPFILES= $(patsubst %.cpp, %.d, $(SOURCE) )


all: $(BINARY)

$(BINARY): $(OBJECT)
	$(CC) -o $@ $^ $(SDL2)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BINARY) $(OBJECT) $(DEPFILES)