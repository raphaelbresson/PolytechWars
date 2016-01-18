#ifndef _DEF_LABEL_H
#define _DEF_LABEL_H
#include "Font.h"
#include "Shader.h"
#include "AbstractWidget.h"
/**
 * \file Label.h
 * \author Raphaël BRESSON, Mahdi HAMMOUCHE
 * \brief Gestion de l'affichage de texte
 * \class Label
 * \brief Représente un objet Texte 2D
 */
class Label : public AbstractWidget
{
public:
  /**
   * \fn Label(std::string const& font,unsigned int tailleFont, Shader *shad, glm::vec2 position)
   * \brief Constructeur+
   */
  Label(std::string const&  font,unsigned int tailleFont, Shader *shad, glm::vec2 const& position);
  /**
   * \fn virtual ~Label()
   * \brief Destructeur
   */
  virtual ~Label();
  
  /**
   * \fn virtual void load(GLenum drawingMethod)
   * \brief Génération des objets OpenGL
   */
  void load(GLenum drawingMethod);
  
  /**
   * \fn virtual void draw(glm::mat4 ortho)
   * \brief Affichage du label
   */
  virtual void draw(glm::mat4 ortho);
  
  /**
   * \fn virtual void cleanUp()
   * \brief Détruit les objets de construction intermédiaires 
   */
  virtual void cleanUp();
  
  /**
   * \fn void setText(std::string const& text, SDL_Color const& color,float taille, GLenum drawingMethod);
   * \brief Changement du texte et regénération
   */
  void setText(std::string const& text, SDL_Color const& color,float taille, GLenum drawingMethod);
  
  void load() {}
protected:
  /**
   * \var std::vector <float> m_coordTex
   * \brief Tableau temporaire de coordonnées de texture
   */
  std::vector <float> m_coordTex;
  /**
   * \var Font m_font
   * \brief Gestion du texte
   */
  Font m_font;
  /**
   * \var unsigned int m_tailleFont
   * \brief Taille de la police
   */
  unsigned int m_tailleFont;
};


#endif