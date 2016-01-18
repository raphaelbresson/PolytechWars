#ifndef _DEF_GUI_FACTORY_H
#define _DEF_GUI_FACTORY_H
#include "Label.h"
/**
 * \file GuiFactory.h
 * \author Raphaël BRESSON, Mahdi HAMMOUCHE
 * \brief Gestion de la construction des objets 2D
 * \def VERTEX_SHADER_GUI
 * \brief Vertex shader pour un objet 2D
 */
#define VERTEX_SHADER_GUI "Shaders/shaderGui.vert"
/**
 * \def FRAGMENT_SHADER_GUI_TEXTURE
 * \brief Fragment shader pour un objet texturé
 */
#define FRAGMENT_SHADER_GUI_TEXTURE "Shaders/shaderGuiTexture.frag"
/**
 * \def FRAGMENT_SHADER_GUI_COLOR
 * \brief Fragment shader pour un objet non texturé (coloré)
 */
#define FRAGMENT_SHADER_GUI_COLOR "Shaders/guiColor.vert"

/**
 * \def FONT_7SEGMENT
 * \brief Fichier de la police "afficheur 7 segments"
 */
#define FONT_7SEGMENT "Fonts/7seg.ttf"
/**
 * \def FONT_COUNTER_STRIKE
 * \brief Fichier de la police du jeu Counter Strike
 */
#define FONT_COUNTER_STRIKE "Fonts/cs.ttf"

/**
 * \def DEFAULT_FONT_SIZE
 * \brief Taille par défault (résolution verticale) du texte affiché à l'écran
 */
#define DEFAULT_FONT_SIZE 50

/**
 * \class GuiFactory 
 * \brief Classe de création d'objets 2D : contient les shaders d'affichage 2D
 */
class GuiFactory
{
public:
  /**
   * \fn GuiFactory()
   * \brief Constructeur
   */
  GuiFactory();
  /**
   * \fn ~GuiFactory()
   * \brief Destructeur
   */
  ~GuiFactory();
  
  /**
   * \fn Label *createLabel(glm::vec2 const& position,std::string const& font)
   * \brief Creation d'un label (texte)
   */
  Label *createLabel(glm::vec2 const& position,std::string const& font);
private:
  /**
   * \var Shader *m_shaderTexture
   * \brief Shader d'objet texturé
   */
  Shader *m_shaderTexture;
  /**
   * \var Shader *m_shaderColor
   * \brief Shader pour les objets non texturés (colorés)
   */
  Shader *m_shaderColor;
};



#endif
