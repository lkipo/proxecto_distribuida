#include <iostream>
#include <stdlib.h>
#include <math.h>

#include <gtkmm.h>


#include <robot.hh>
#include <swarm.hh>
#include <environment.hh>
#include <simulation.hh>
#include <simulation-plot.hh>

#include "aligningRobot.hh"

// TODO: Implement a function to analyse the swarm
void
analyseSwarm(const mrs::SwarmPtr & swarmp)
{
  
  return;
}


int
main()
{
  // Create an environment for the swarm
  mrs::Environment env(mrs::Position2d(-15,-15), mrs::Position2d(15,15));
  // TODO: You can change the settings of the robot to maximise
  // aggregation
  // Settings of the robots, different than the default settings
  mrs::RobotSettings rSettingsRed = {0.15,     // Robot radius
				     2.0,      // Perceptual range
				     0.0,      // Min speed
				     0.75,     // Max speed
				     0.0,      // Min Omega
				     1.5,      // Max Omega
				     true,     // Visible
				     {1,0,0}}; // Colour

  mrs::RobotSettings rSettingsBlue = {0.2,     // Robot radius
				      2.0,      // Perceptual range
				      0.0,      // Min speed
				      0.75,     // Max speed
				      0.0,      // Min Omega
				      1.5,      // Max Omega
				      true,     // Visible
				      {0,0,1}}; // Colour
  
  

  // TODO: You can change th number of robots in the
  // environment. Notice that it might not be possible to place all
  // the robots in the environment if there is no space left.
  // Create a random swarm of 20 robots
  const int numberOfRobots(100);
  // Initialise random number generator
  srand((unsigned int) time(0));

  
  // Create a random swarm of aggregating robots in the environment 
  mrs::SwarmPtr swarmp = std::make_shared<mrs::Swarm>();
  
  for (unsigned int ii = 0 ; ii < numberOfRobots; ii++) {
    int trials(100);
    mrs::Position2d pt;
    if (ii < (numberOfRobots / 2))
      pt = env.random(rSettingsRed.radius, swarmp, trials);
    else
      pt = env.random(rSettingsBlue.radius, swarmp, trials);
    if (trials <= 0)
      std::cerr << "Error creating random swarm" << std::endl;
    mrs::RobotPtr rp(nullptr);
    if (ii < (numberOfRobots / 2))
      rp = std::make_shared<AligningRobot>(ii, pt,
					   rSettingsRed,
					   mrs::Velocity2d::Random());
    else
      rp = std::make_shared<AligningRobot>(ii, pt,
					   rSettingsBlue,
					   mrs::Velocity2d::Random());
    swarmp->push_back(rp);
    // Change color of half of the robots. Comment the two lines below
    // to have all robots with the same colour
  }

  // Create a Simulation object to simulate the swarm
  mrs::SimulationPtr simp(std::make_shared<mrs::Simulation>(swarmp));
  simp->tMax(200);
  // Run the simulation
  simp->run();

  // Uncomment this if you want to inspect the trajectory as a text
  // file (see header file simulation.hh to check for the format)
  // simp->saveTraj("trajectory.txt");
  for (unsigned int ii = 0; ii < simp->size(); ii++)
    analyseSwarm((*simp)[ii]);
  
  // Show the animation of the retulting swarm trajectory
  Glib::RefPtr<Gtk::Application>  app = Gtk::Application::create("es.usc.mrs");
  mrs::SimulationWindow dsp(simp, env);
  app->run(dsp);
  
  return 0;
}
