#ifndef _DEF_ABSTRACT_BUTTON_H_
#define _DEF_ABSTRACT_BUTTON_H_

#include "AbstractWidget.h"
#include "Input.h"
/**
 * \file AbstractButton.h
 * \brief Définit un type polymorphe pour les boutons
 * \class AbstractButton
 * \brief Type polymorphe pour les boutons
 */
class AbstractButton : public AbstractWidget
{
public:
  /**
   * \fn AbstractButton(Shader* shad, glm::vec2 position, Input *input)
   * \brief Constructeur
   */
  AbstractButton(Shader* shad, glm::vec2 position, Input *input);
  /**
   * \fn ~AbstractButton()
   * \brief Destructeur
   */
  ~AbstractButton();
  /**
   * \fn virtual void draw(glm::mat4 ortho)
   * \brief Méthode d'affichage (virtuelle pure)
   */
  virtual void draw(glm::mat4 ortho) = 0;
  /**
   * \fn void setDimensions(glm::vec2 dim)
   * \brief Modificateur de dimensions
   */
  void setDimensions(glm::vec2 dim) { m_dimensions = dim; }
  /**
   * \fn glm::vec2 getDimensions()
   * \brief Retourne les dimensions
   */
  glm::vec2 getDimensions() const { return m_dimensions; }
protected:
  /**
   * \fn void eventHandler()
   * \brief Gère les évênements
   */
  void eventHandler();
  /**
   * \fn void onClickEvent()
   * \brief Virtuelle pure pour gérer le clic de souris
   */
  virtual void onClickEvent() = 0;
  /**
   * \var bool m_stopThread
   * \brief Booléen pour stopper les threads de gestion des évênements
   */
  bool m_stopThread;
  /**
   * \var std::thread m_threadClickEvent
   * \brief Thread de gestion du clic de souris
   */
  std::thread m_threadClickEvent;
  /**
   * \var std::condition_variable* m_clicked
   * \brief Condition de gestion du clic de souris
   */
  std::condition_variable* m_clicked;
  /**
   * \var std::unique_lock<std::mutex> m_clickedLock
   * \brief Mutex de gestion du clic de souris
   */
  std::unique_lock<std::mutex> m_clickedLock;
  /**
   * \var glm::vec2 m_dimensions
   * \brief Dimensions du bouton
   */
  glm::vec2 m_dimensions;
};
#endif