#include "CameraFlightSimulator.h" 

CameraFlightSimulator::CameraFlightSimulator(glm::vec3 const& position, glm::vec3 const& axe_vertical, glm::vec3 const& cible, float proche, float loin, float ratioResolution, MeshNode* attached) : AbstractCamera(position,axe_vertical,cible,proche,loin,ratioResolution), m_attached(attached), m_sensibilite(0.3f)
{
  perspective();
}

CameraFlightSimulator::~CameraFlightSimulator()
{ 
}

void CameraFlightSimulator::onEvent(Input const& input)
{
  if(m_active)
  {
    if(input.getKey(SDL_SCANCODE_UP))//controle de la vitesse
    {
      m_vitesse += 0.1f;
      if(m_vitesse > 100.0f)
	m_vitesse = 100.0f;
    }else if(input.getKey(SDL_SCANCODE_DOWN))
    {
      m_vitesse -= 0.1f;
      if(m_vitesse < 0.0f)
	m_vitesse = 0.0f;
    }
  }
  if(m_vitesse > 0.0f)
  {
    glm::vec3 anglesEuler = glm::vec3(0.0, 0.0, 0.0);//angles d'Euler -> controle des rotations du vaisseau
    if(m_active)
    {
      if(input.getKey(SDL_SCANCODE_W))// -> tonneau 
	anglesEuler.x += m_sensibilite;
      else if(input.getKey(SDL_SCANCODE_S))
	anglesEuler.x -= m_sensibilite;
      if(input.getKey(SDL_SCANCODE_Q))// -> looping
	anglesEuler.y += m_sensibilite;
      else if(input.getKey(SDL_SCANCODE_E))
	anglesEuler.y -= m_sensibilite;  
      if(input.getKey(SDL_SCANCODE_A))// -> lacet
	anglesEuler.z -= m_sensibilite;
      else if(input.getKey(SDL_SCANCODE_D))
	anglesEuler.z += m_sensibilite;
    }
    //calcul de la matrice de rotation -> calculées à l'aide des angles d'Euler  
    glm::quat yaw_pitch_roll;
    anglesEuler *= M_PI / 180.0;
    yaw_pitch_roll = glm::quat(anglesEuler);
    m_rotationMatrix *= glm::mat4_cast(yaw_pitch_roll);
    orienter();
    deplacer(m_orientation * m_vitesse);
    lookAt();
  }
}

void CameraFlightSimulator::orienter()
{
  glm::mat4 translation(1.0f), total(1.0f); 
    translation = glm::translate(translation,m_attached->getPosition() - m_position);
  total = translation * m_rotationMatrix * glm::inverse(translation); 
  //calcul et normalisation des vecteurs
  m_axe_vertical = glm::vec3(total * glm::vec4(0.0f,1.0f,0.0f,0.0f));
  m_orientation = glm::vec3(total * glm::vec4(0.0f,0.0f,1.0f,0.0f));
  m_droite = glm::vec3(total * glm::vec4(1.0f,0.0f,0.0f,0.0f));
  m_axe_vertical = glm::normalize(m_axe_vertical);
  m_orientation = glm::normalize(m_orientation);
  m_droite = glm::normalize(m_droite);
  m_attached->setRotationMatrix(m_rotationMatrix);// Rotation de l'objet
}

void CameraFlightSimulator::deplacer(glm::vec3 deplacement)
{
  //calcul de la distance entre l'objet et la caméra
    glm::vec3 posRel = m_attached->getPosition() - m_position;//calcul de la distance entre la camera et l'objet
    float distance = sqrt(glm::dot(posRel,posRel));
    m_attached->setPosition(m_attached->getPosition() + deplacement); //déplacement de l'objet
    m_position = m_attached->getPosition() - (distance * m_orientation);//on place la camera derriere l'objet
    m_cible = m_position + m_orientation;
}

