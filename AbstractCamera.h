#ifndef _DEF_ABSTRACT_CAMERA_H
#define _DEF_ABSTRACT_CAMERA_H

#include "Include_GL_and_GLM.h"
#include "Input.h"
/**
 * \file AbstractCamera.h
 * \brief Définit un type polymorphe pour les caméras
 * \class AbstractCamera
 * \brief Type polymorphe pour les caméras (point de vue sur le monde 3D)
 */
class AbstractCamera
{
public:
  /**
   * \fn AbstractCamera(glm::vec3 const& position, glm::vec3 const& axe_vertical, glm::vec3 const& cible, float proche, float loin, float ratioResolution)
   * \brief Construit une caméra et l'initialise en fonction de sa position de son axe vertical et de son point ciblé
   */
  AbstractCamera(glm::vec3 const& position, glm::vec3 const& axe_vertical, glm::vec3 const& cible, float proche, float loin, float ratioResolution): 
      m_position(position), m_axe_vertical(axe_vertical), m_cible(cible),m_proche(proche), m_loin(loin), m_ratioResolution(ratioResolution),m_vitesse(0.0f),m_active(false)
      {
	m_orientation = cible - position;
	m_droite = glm::cross(axe_vertical,m_orientation);
	lookAt();
      }    
  /**
   * \fn virtual ~AbstractCamera()
   * \brief Destructeur
   */
  virtual ~AbstractCamera(){}
  /**
   * \fn virtual glm::mat4 lookAt()
   * \brief Méthode virtuelle qui doit construire et retourner la matrice de modelview
   */
  virtual void lookAt()
  {
    m_modelview = glm::lookAt(m_position,m_cible,m_axe_vertical);
  }
  
  /**
   * \fn virtual glm::mat4 perspective()
   * \brief Méthode virtuelle pure qui doit construire et retourner la matrice de projection
   */
  virtual void perspective(){};

  /**
   * \fn virtual void onEvent(Input &input)
   * \brief Méthode virtuelle pure qui traite les évênements pour la caméra appelée à chaque tour de boucle
   */
  virtual void onEvent(Input const& input) = 0;
  
  /**
   * \fn glm::mat4 getProjection() const
   * \brief retourne la matrice de projection
   */
  glm::mat4 getProjection() const
  {
    return m_projection;
  }
  /**
   * \fn glm::mat4 getModelview() const
   * \brief retourne la matrice de modelview
   */
  glm::mat4 getModelview() const
  {
    return m_modelview;
  }
  /**
   * \fn virtual glm::vec3 getPosition() const
   * \brief Méthode virtuelle pure qui retourne la position
   */
  virtual glm::vec3 getPosition() const = 0;
  /**
   * \fn float getVitesse() const
   * \brief Retourne la vitesse
   */
  float getVitesse() const { return m_vitesse; }
  /**
   * \var bool isActive() const
   * \brief Savoir si la caméra est active(true) ou non(false)
   */
  bool isActive() const { return m_active; }
  /**
   * \var void setActive(bool active)
   * \brief Déterminer si la caméra est active(true) ou non(false)
   */
  void setActive(bool active) { m_active = active; }
  
protected:
  /**
   * \var glm::vec3 m_position
   * \brief Position de la caméra dans le monde 3D
   */
  glm::vec3 m_position;
  /**
   * \var glm::vec3 m_axe_vertical
   * \brief Axe vertical de la caméra
   */
  glm::vec3 m_axe_vertical;
  /**
   * \var glm::vec3 m_cible
   * \brief Point ciblé par la caméra
   */
  glm::vec3 m_cible;
  /**
   * \var glm::vec3 m_orientation
   * \brief Vecteur orientation de la caméra
   */
  glm::vec3 m_orientation;
  /**
   * \var glm::vec m_droite
   * \brief Vecteur normal à l'orientation et à l'axe vertical -> deplacement lateral
   */
  glm::vec3 m_droite;
  /**
   * \var glm::vec3 m_proche
   * \brief Distance minimale de la caméra pour affichage
   */
  float m_proche;
  /**
   * \var glm::vec3 m_loin
   * \brief Distance maximale de la caméra pour affichage
   */
  float m_loin;
  /**
   * \var float m_ratioResolution
   * \brief Largeur de la fenêtre / Hauteur de la fenêtre
   */
  float m_ratioResolution;
  /**
   * \var float m_vitesse;
   * \brief Vitesse de déplacement de la caméra
   */
  float m_vitesse;
  /**
   * \var glm::mat4 m_projection
   * \brief Matrice de projection
   */
  glm::mat4 m_projection;
  /**
   * \var glm::mat4 m_modelview
   * \brief Matrice de modelview
   */
  glm::mat4 m_modelview;
  /**
   * \var bool m_active
   * \brief Détermine si la caméra est active ou non
   */
  bool m_active;
};

#endif
