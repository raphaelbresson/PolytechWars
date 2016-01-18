#ifndef _DEF_FONT_H
#define _DEF_FONT_H
#include "Texture.h"
/**
 * \file Font.h
 * \author Raphaël BRESSON, Mehdi HAMMOUCHE
 * \brief Gestion de la génération de texte
 * \class Font
 * \brief Gère la conversion de texte en texture GL à partir d'une police
 */
class Font : public Texture
{
public:
  /**
   * \fn Font(std::string const& fn_font, unsigned int taille)
   * \brief Construit une police à partir du fichier fn_font
   */
  Font(std::string const& fn_font, unsigned int taille);
  /**
   * \fn void createText(std::string const& text, SDL_Color color)
   * \brief Crée les objets GL à partir du texte et de la couleur en argument
   */
  void createText(std::string const& text, SDL_Color color);
  /**
   * \fn void createTextWithBackground(std::string const& text, SDL_Color textColor,SDL_Color backgroundColor)
   * \brief Crée les objets GL à partir du texte et de la couleur en argument avec une couleur de fond
   */
  void createTextWithBackground(std::string const& text, SDL_Color textColor,SDL_Color backgroundColor);
  /**
   * \fn ~Font()
   * \brief Destructeur
   */
  ~Font();
  
  /**
   * \fn unsigned int getHeight()
   * \brief Retourne la hauteur du texte généré
   */
  unsigned int getHeight(){ return m_h; }
  /**
   * \fn unsigned int getWidth()
   * \brief Retourne la largeur du texte généré
   */
  unsigned int getWidth() { return m_w; }
  
 
private:
  /**
   * \var TTF_Font *m_font
   * \brief Structure de gestion de police de la SDL
   */
  TTF_Font *m_font;
  /**
   * \var unsigned int m_h
   * \brief Hauteur du texte généré
   */
  unsigned int m_h;
  /**
   * \var unsigned int m_w
   * \brief Largeur du texte généré
   */
   unsigned int m_w;
  
};

#endif