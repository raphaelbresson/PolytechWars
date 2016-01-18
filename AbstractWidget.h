#ifndef _DEF_ABSTRACT_WIDGET_H_
#define _DEF_ABSTRACT_WIDGET_H_
#include "AbstractGraphicObject.h"

/**
 * \file AbstractWidget.h
 * \brief Définit un type polymorphe pour les objets 2D
 * \class AbstractWidget
 * \brief Classe abstraite mère de tous les objets 2D
 */
class AbstractWidget: public AbstractGraphicObject
{
public:
  /**
   * \fn AbstractWidget(glm::vec2 position)
   * \brief Crée un objet 2D à la position sur l'écran indiquée en argument
   */
  AbstractWidget(Shader *shader,glm::vec2 position): AbstractGraphicObject(shader), m_position(position) {}
  /**
   * \fn virtual ~AbstractWidget()
   * \brief Détruit un objet2D et libère ses ressources
   */
  virtual ~AbstractWidget() {}
  /**
   * \fn glm::vec2 getPosition()
   * \brief Retourne la position d l'objet sur l'écran
   */
  glm::vec2 getPosition();
  /**
   * \fn void setPosition(glm::vec2 const& position)
   * \brief Change la position d'un objet 2D sur l'écran
   */
  void setPosition(glm::vec2 const& position);
  
  /**
   * \fn virtual void draw(glm::mat4 ortho)
   * \brief Méthode virtuelle pure d'affichage)
   */
  virtual void draw(glm::mat4 ortho) = 0;
  
protected:
  /**
   * \var glm::vec2 m_position
   * \brief Position de l'objet sur l'écran
   */
  glm::vec2 m_position;
};

#endif