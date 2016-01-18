#ifndef _DEF_CAMERA_FPS_H
#define _DEF_CAMERA_FPS_H

#include "AbstractCamera.h"
/**
 * \file CameraFPS.h
 * \brief Définition de la caméra à la première personne
 * \class CameraFPS
 * \brief Caméra de type Freefly à deux degrés de liberté en fixant l'axe vertical
 */
class CameraFPS : public AbstractCamera
{
public:
  /**
   * \fn CameraFPS(glm::vec3 const& position, glm::vec3 const& axe_vertical, glm::vec3 const& cible, float proche, float loin, float ratioResolution, float vitesse, float sensibilite)
   * \brief Création et initialisation
   */
  CameraFPS(glm::vec3 const& position, glm::vec3 const& axe_vertical, glm::vec3 const& cible, float proche, float loin, float ratioResolution, float vitesse, float sensibilite);
  /**
   * \fn virtual ~CameraFPS() 
   * \brief Destructeur
   */
  ~CameraFPS();
  /**
   * \fn virtual void onEvent(Input const& input)
   * \brief Traitement des évênements clavier et souris
   */
  virtual void onEvent(Input const& input);
  /**
   * \fn virtual glm::mat4 perspective()
   * \brief Méthode virtuelle qui doit construire et retourner la matrice de projection pour prendre en compte le zoom
   */
  virtual void perspective()
  {
    m_projection = glm::perspective(m_zoom, m_ratioResolution, m_proche, m_loin);
  }
  /**
   * \fn glm::vec3 getPosition() const
   * \brief retourne la position
   */
  virtual glm::vec3 getPosition() const
  {
    return m_position;
  }
protected:
  /**
   * \fn void orienter(int xRel, int yRel)
   * \brief Oriente la caméra en fonction du déplacement de la souris
   */
  void orienter(int xRel, int yRel);
  /**
   * \fn void deplacer(glm::vec3 const& deplacement)
   * \brief Déplace la caméra
   */
  void deplacer(glm::vec3 const& deplacement);
  /**
   * \fn void zoomer()
   * \brief Effectue un zoome dans le monde 3D
   */
  void zoomer(int zoom);
  /**
   * \var float m_phi
   * \brief Angle de rotation par rapport à l'axe vertical
   */
  float m_phi;
  /**
   * \var float m_theta
   * \brief Angle de rotation par rapport au vecteur lateral
   */
  float m_theta;
  /**
   * \var float m_zoom;
   * \brief Zoom de la caméra
   */
  float m_zoom;
  /**
   * \var float m_sensibilite;
   * \brief Vitesse de rotation de la caméra
   */
  float m_sensibilite;
};

#endif
