#include "aligningRobot.hh"

// TODO: Implement here your aligning robot

AligningRobot::AligningRobot(unsigned int id, const mrs::Position2d &p,
                             const mrs::RobotSettings &settings,
                             const mrs::Velocity2d &vel) : mrs::Robot(id, p, settings, vel)
{
}

// const mrs::Velocity2d &
// meanVel(const std::vector<mrs::RobotPtr> &swarm, const mrs::RobotPtr)
// {
//   mrs::Velocity2d total = mrs::Velocity2d::Zero();

//   for (const mrs::RobotPtr &neighbor : swarm)
//   {
//     if (robot->sameColor(neighbor))
//     {
//       total = total + neighbor->velocity();
//     }
//   }

//   mean_vel = total / swarm.size(); // ? POSIBLEMENTE ESTEA MAL, TODO REVISAR
//   mean_vel.normalize();            // ? POSIBLEMENTE ESTEA MAL, TODO REVISAR
//   mean_vel *settings().vMax;       // ? POSIBLEMENTE ESTEA MAL, TODO REVISAR

//   return mean_vel;
// }

// Method to compute the action
const mrs::Velocity2d &
AligningRobot::action(const std::vector<mrs::RobotPtr> &swarm)
{
  // Probability of changing direction randomly
  const int MAXIMO(1e6);
  float num(float(rand() % (MAXIMO + 1)));
  num /= float(MAXIMO);

  // mrs::Position2d neigborhood_centroid = mrs::average(swarm);

  if ((swarm.size()) > 0)
  {
    mrs::Velocity2d total = mrs::Velocity2d::Zero();

    for (const mrs::RobotPtr &neighbor : swarm)
    {
      if (sameColor(neighbor))
      {
        total = total + neighbor->velocity();
      }
    }

    // !comentable
    total = total + velocity(); // TODO CAMBIAR ESTO
    // count++; // TODO CAMBIAR ESTO
    

    m_vel = total / (swarm.size()+1); // ? POSIBLEMENTE ESTEA MAL, TODO REVISAR
    m_vel.normalize();            // ? POSIBLEMENTE ESTEA MAL, TODO REVISAR
    m_vel = m_vel*settings().vMax;       // ? POSIBLEMENTE ESTEA MAL, TODO REVISAR
  }

  else if (num < 0.05)
  {
    m_vel = mrs::Velocity2d::Random();
  }

  return m_vel;
}
// Method to set m_vel to zero
// void zeroVel() { m_vel = mrs::Velocity2d::Zero(); }

// Method to generate a random velocity
// void rndVel() { m_vel = mrs::Velocity2d::Random(); }

// Method to clone the Aligning robot
mrs::RobotPtr
AligningRobot::clone() const
{
  AligningRobotPtr newRobot = std::make_shared<AligningRobot>(m_id, m_pos, m_settings, m_vel);
  newRobot->m_steps = m_steps;
  newRobot->m_stepsChange = m_stepsChange;

  return std::dynamic_pointer_cast<mrs::Robot>(newRobot);
}
