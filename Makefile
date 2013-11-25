# this Makefile is intended to make any of the examples in this directory

# the following lines pertain to using sound
# if you download FMOD onto your own machine, change the line below
#FMOD_DIR = /usr/local/dept/apps/fmod
#FMOD_INCLUDE = -I$(FMOD_DIR)/api/inc -I$(FMOD_DIR)/examples/common
#FMOD_LIB = $(FMOD_DIR)/api/lib/libfmodex64.so

# the following lines pertain to setting up compiler options and libraries
OPTS = -Wall -Wno-deprecated -g
LIBS = -lGL -lglut -lm
ARCH := $(shell uname)
ifeq ($(ARCH), Linux)
else
 MACOSX_DEFINE = -DMACOSX -I/sw/include
 FRAMEWORK = -framework GLUT -framework OpenGL
 LIBPATH = -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
 LIBRARIES = -lGL -lGLU -lm -lobjc -lstdc++
 LIBS = -I/usr/common/include -I/usr/include/GL -L/sw/lib -L/System/Library/Frameworks/OpenGL.framework/Libraries -framework GLUT -framework OpenGL -lGL -lm -lobjc -lstdc++
 # LIBS = $(FRAMEWORK) $(LIBPATH) $(LIBRARIES)

endif

# here are the usual make rules

dominion:	dominion.o texture.o card.o
	g++ $(OPTS) -o dominion dominion.o texture.o card.o $(LIBS)
	# g++ $(OPTS) -o dominion dominion.o texture.o card.o $(LIBS)

dominion.o:	dominion.cpp
	g++ $(OPTS)  -c dominion.cpp

texture.o: texture.cpp texture.h
	g++ $(OPTS) -c texture.cpp

network.o: network.cpp network.h
	g++ $(OPTS) -c network.cpp

# cardDriver: cardDriver.o card.o
# 	g++ -o cardDriver cardDriver.o card.o

# cardDriver.o: cardDriver.cpp card.h
# 	g++ -g -c cardDriver.cpp

card.o: card.cpp card.h
	g++ -g -c card.cpp

clean:
	rm *.o dominion *~
