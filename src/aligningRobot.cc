#include "aligningRobot.hh"

// TODO: Implement here your aligning robot

AligningRobot::AligningRobot(unsigned int id, const mrs::Position2d & p, 
			     const mrs::RobotSettings & settings,
			     const mrs::Velocity2d & vel) : mrs::Robot(id, p, settings, vel)
{
}

// Method to compute the action
const mrs::Velocity2d &
AligningRobot::action(const std::vector<mrs::RobotPtr> & swarm)
{
  // TODO

  return m_vel;
}

// Method to clone the Aligning robot
mrs::RobotPtr
AligningRobot::clone() const
{
  AligningRobotPtr newRobot = std::make_shared<AligningRobot>(m_id, m_pos, m_settings, m_vel);
  newRobot->m_steps = m_steps;
  newRobot->m_stepsChange = m_stepsChange;
  
  return std::dynamic_pointer_cast<mrs::Robot>(newRobot);
}
