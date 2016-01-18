#ifndef APPLICATION_CONTROL_H
#define APPLICATION_CONTROL_H

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Include_GL_and_GLM.h"
#include "Input.h"
#include "SceneManager.h"

/**
 * \file ApplicationControl.h
 * \author Raphaël BRESSON, Mahdi HAMMOUCHE
 * \brief Gestion de la SDL et de OpenGL ainsi que du SceneManager
 * \class ApplicationControl
 * \brief Classe repésentant globalement le programme graphique
 */

class ApplicationControl
{
public:
  /**
   * \fn ApplicationControl(unsigned int windowWidth = 800, unsigned int windowHeight = 600)
   * \brief Crée la fenetre à l'aide des dimensions en argument
   */
  ApplicationControl(unsigned int windowWidth = 800, unsigned int windowHeight = 600);
  /**
   * \fn ~ApplicationControl()
   * \brief Destructeur
   */
  ~ApplicationControl();
  /**
   * \fn bool init()
   * \brief initialisation de la SDL, de OpenGL ainsi que de la fenêtre 
   */
  bool init();
  /**
   * \fn bool execute()
   * \brief Exécution du programme graphique
   */
  bool execute();
private:
  /**
   * \fn bool initSDL()
   * \brief Initialise la SDL et renvoie true si succès
   */
  bool initSDL();
  /**
   * \fn bool initGL()
   * \brief Initialise OpenGL et renvoie true si succès
   */
  bool initGL();
  /**
   * \var unsigned int m_windowWidth
   * \brief Hauteur de la fenêtre
   */
  unsigned int m_windowWidth;
  /**
   * \var unsigned int m_windowHeight
   * \brief Largeur de la fenêtre
   */
  unsigned int m_windowHeight;
  
  std::string m_windowTitle;
  /**
   * \var SceneManager m_sceneMgr
   * \brief Gestionnaire d'affichage
   */
  SceneManager m_sceneMgr;
  /**
   * \var SDL_Window *m_window
   * \brief Fenêtre SDL
   */
  SDL_Window *m_window;
  /**
   * \var SDL_GLContext m_context
   * \brief Contexte OpenGL pour la SDL
   */
  SDL_GLContext m_context;
};

#endif