GXX = g++
CXXFLAGS = -I. -std=c++11 `pkg-config --cflags eigen3 yaml-cpp gtkmm-3.0` -Wall
LDFLAGS = `pkg-config --libs yaml-cpp gtkmm-3.0`
AR = ar 

SRC = simulation-plot.cc simulation.cc environment.cc swarm.cc robot.cc 

OBJ = $(SRC:.cc=.o)

%.o: %.cc %.hh
	$(GXX) $(CXXFLAGS) -o $@ -c $<

all: libMRS.a aligningSwarm
 
aligningSwarm: aligningSwarm.cc aligningRobot.o
	$(GXX) $(CXXFLAGS) -I. -o $@ $^ -L. -lMRS $(LDFLAGS)

libMRS.a: $(OBJ)
	$(AR) rcs $@ $^
	ranlib $@

aligningRobot.o: aligningRobot.cc aligningRobot.hh	
robot.o: robot.cc robot.hh
swarm.o: swarm.cc swarm.hh
environment.o: environment.cc environment.hh

clean:
	rm *.o *~ libMRS.a aligningSwarm
