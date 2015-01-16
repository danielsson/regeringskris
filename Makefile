CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -D_REENTRANT -pthread -I/sw/include/root  -std=c++11
LDFLAGS=-g
LDLIBS=-L/sw/lib/root -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint \
	   -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lz -L/sw/lib -lfreetype -lz \
	   -Wl,-framework,CoreServices -Wl,-framework,ApplicationServices -pthread -Wl,-rpath,/sw/lib/root \
	   -lm -ldl

SRCS=main.cpp GameEngine.cpp world/entity.cpp world/env.cpp world/loader.cpp fight/kabbla.cpp util.cpp json/json.cc
OBJS=$(subst .cc,.o, $(subst .cpp,.o,$(SRCS)))

all: regeringskris

regeringskris: $(OBJS)
	$(CXX) $(LDFLAGS) -o regeringskris $(OBJS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend