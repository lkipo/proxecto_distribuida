#ifndef ALIGNING_ROBOT_HH
#define ALIGNING_ROBOT_HH
#include "robot.hh"


class AligningRobot;
// Definition of a pointer to an aggregation robot (unnecessary)
typedef std::shared_ptr<AligningRobot> AligningRobotPtr;

class AligningRobot : public mrs::Robot {
public:

  // Constructor for the Flocking Robot
  AligningRobot(unsigned int id, const mrs::Position2d & p, 
		const mrs::RobotSettings & settings = mrs::defaultRobotSettings,
		const mrs::Velocity2d & vel = mrs::Velocity2d::Random());

  // Method to compute the action
  const mrs::Velocity2d & action(const std::vector<mrs::RobotPtr> & swarm);


  // Name of the type of flocking robot
  std::string name() const {return std::string("Aln");}

  // Method to clone the flocking robot
  mrs::RobotPtr clone() const;
private:
  int m_steps;
  int m_stepsChange;
};


#endif
