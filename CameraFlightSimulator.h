#ifndef _DEF_CAMERA_FLIGHT_SIMULATOR_H
#define _DEF_CAMERA_FLIGHT_SIMULATOR_H

#include "AbstractCamera.h"
#include "MeshNode.h"
/**
 * \file CameraFlightSimulator.h
 * \brief Implémentation de la caméra de simulateur de vol
 * \class CameraFlightSimulator
 * \brief Implémentation de la caméra de simulateur de vol
 */
class CameraFlightSimulator : public AbstractCamera
{
public:
  /**
   * \fn CameraFlightSimulator(glm::vec3 const& position, glm::vec3 const& axe_vertical, glm::vec3 const& cible, float proche, float loin, float ratioResolution)
   * \brief Constructeur de caméra de simulateur de vol
   */
  CameraFlightSimulator(glm::vec3 const& position, glm::vec3 const& axe_vertical, glm::vec3 const& cible, float proche, float loin, float ratioResolution, MeshNode* attached);
  /**
   * \fn virtual ~CameraFlightSimulator()
   * \brief Destructeur
   */
  virtual ~CameraFlightSimulator();
  /**
   * \fn virtual void onEvent(Input const& input)
   * \brief Traitement des évênements clavier
   */
  virtual void onEvent(Input const& input);
  
  /**
   * \fn virtual glm::vec3 getPosition() const
   * \brief Méthode virtuelle qui retourne la position
   */
  virtual glm::vec3 getPosition() const
  {
     return m_attached->getPosition();
  }
   /**
   * \fn virtual glm::mat4 perpective()
   * \brief Méthode virtuelle qui doit construire et retourner la matrice de projection pour prendre en compte le zoom
   */
  virtual void perspective()
  {
    m_projection = glm::perspective(70.0f, m_ratioResolution, m_proche, m_loin);
  }
  
private:
  /**
   * \fn void deplacer(glm::vec3 deplacement)
   * \brief Déplacement de la caméra
   */
  void deplacer(glm::vec3 deplacement);
  /**
   * \fn void orienter()
   * \brief Déplacement de la caméra
   */
  void orienter();
  /**
   * \var glm::mat4 m_rotation
   * \brief Matrice de la rotation du repère de la caméra par rapport au repère (1,0,0),(0,1,0),(1,0,0)
   */
  glm::mat4 m_rotationMatrix;
  /**
   * \var float m_vitesse
   * \brief Vitesse de la caméra
   */
  MeshNode* m_attached;
  /**
   * \var float m_sensibilite
   * \brief Vitesse de rotation de la caméra
   */
  float m_sensibilite;
};


#endif