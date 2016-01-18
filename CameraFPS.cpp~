#include "CameraFPS.h"

CameraFPS::CameraFPS(glm::vec3 const& position, glm::vec3 const& axe_vertical, glm::vec3 const& cible, float proche, float loin, float ratioResolution, float vitesse, float sensibilite):
  AbstractCamera(position,axe_vertical,cible,proche,loin,ratioResolution), m_zoom(70.0f), m_sensibilite(sensibilite)
{
  m_vitesse = vitesse;
  glm::vec3 orientation = glm::normalize(cible - position);
   if(m_axe_vertical.x == 1.0) 
   {
    m_phi = asin(orientation.x);
    m_theta = acos(orientation.y / cos(m_phi));
     if(m_orientation.y < 0)
       m_theta = - m_theta;
   }else if(m_axe_vertical.y == 1.0)
   {
     m_phi = asin(orientation.y);
     m_theta = acos(orientation.z / cos(m_phi));
     if(m_orientation.z < 0)
       m_theta = - m_theta;
   } 
   else
   {   
     m_phi = asin(orientation.z);
     m_theta = acos( - orientation.x / cos(m_phi));
     if(m_orientation.x < 0)
       m_theta = - m_theta;
   }
   m_phi = m_phi * 180 / M_PI;
   m_theta = m_theta * 180 / M_PI;
   perspective();
}

CameraFPS::~CameraFPS()
{
  
}

void CameraFPS::onEvent(Input const& input)
{
  //évênements souris
  if(input.mouseMove())
    orienter(input.getXRel(), input.getYRel());//changement d'orientation
  //évênements claviers
  glm::vec3 deplacement(0.0f,0.0f,0.0f);
  float zoom = 0.0f;
  if(input.getKey(SDL_SCANCODE_W))//Z pour un clavier francophone
    deplacement += m_vitesse * m_orientation;
  if(input.getKey(SDL_SCANCODE_S))
    deplacement -= m_vitesse * m_orientation;
  if(input.getKey(SDL_SCANCODE_A))//Q pour un clavier francophone
    deplacement += m_vitesse * m_droite;
  if(input.getKey(SDL_SCANCODE_D))
    deplacement -= m_vitesse * m_droite;
  if(input.getKey(SDL_SCANCODE_KP_PLUS)) // touche + du pavé numérique pour zoomer
    zoom += 1.0f;
  if(input.getKey(SDL_SCANCODE_KP_MINUS)) // touche - du pavé numérique pour dezoomer
    zoom -= 1.0f;
  if(zoom!=0.0f)
    zoomer(zoom);
  if(deplacement != glm::vec3(0.0f,0.0f,0.0f))
    deplacer(deplacement); // déplacement de la camera
  m_cible = m_position + m_orientation;
  if(deplacement != glm::vec3(0.0f,0.0f,0.0f) || input.mouseMove())
    lookAt();
}

void CameraFPS::zoomer(int zoom)
{
  m_zoom += zoom;
  if(m_zoom > 120.0f)
    m_zoom = 120.0f;
  if(m_zoom < 30.0f)
    m_zoom = 30.0f;
  perspective();
}

void CameraFPS::orienter(int xRel, int yRel)
{
  m_phi -= ((float)yRel * m_sensibilite);
  m_theta -= ((float)xRel * m_sensibilite);
  if(m_phi > 89.0)
    m_phi = 89.0;
  if(m_phi < -89.0)
    m_phi = -89.0;
  
  float phiRadian = m_phi * M_PI / 180.0;
  float thetaRadian = m_theta * M_PI / 180.0;
  
  if(m_axe_vertical.x == 1.0)
  {
    m_orientation.x = sin(phiRadian);
    m_orientation.y = cos(phiRadian) * cos(thetaRadian);
    m_orientation.z = cos(phiRadian) * sin(thetaRadian);
  }else if(m_axe_vertical.y == 1.0)
  {
    m_orientation.x = cos(phiRadian) * sin(thetaRadian);
    m_orientation.y = sin(phiRadian);
    m_orientation.z = cos(phiRadian) * cos(thetaRadian);
  }else
  {
    m_orientation.x = cos(phiRadian) * cos(thetaRadian);
    m_orientation.y = cos(phiRadian) * sin(thetaRadian);
    m_orientation.z = sin(phiRadian);
  }
  m_droite =  glm::cross(m_axe_vertical,m_orientation);
  m_cible = m_position + m_orientation;
}

void CameraFPS::deplacer(glm::vec3 const& deplacement)
{
  m_position += deplacement;
}
