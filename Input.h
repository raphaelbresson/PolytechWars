#ifndef INPUT_H
#define INPUT_H
#include "Include_GL_and_GLM.h"
#include <SDL2/SDL.h>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <chrono>
/**
 * \file Input.h
 * \authors Raphaël BRESSON, Mehdi HAMMOUCHE
 * 
 * \class Input
 * \brief gestion des évênements
 */
class Input
{
public:
  /**
   * \fn Input(int maxY)
   * \brief Constructeur
   */
  Input(int maxY);
  /**
   * \fn Input()
   * \brief Destructeur
   */
  ~Input();
  /**
   * \fn void update()
   * \brief Mise à jour des évênements
   */
  void update();
  /**
   * \fn bool getKey(const SDL_Scancode i) const
   * \brief Renvoie true si la touche i est enfoncée false sinon
   */
  bool getKey(const SDL_Scancode i) const;
  /**
   * \fn bool getKeyRelease(const SDL_Scancode i) const
   * \brief Renvoie true si la touche i est relachée false sinon
   */
  bool getKeyRelease(const SDL_Scancode i) const;
  /**
   * \fn bool mouseMove() const
   * \brief Renvoie true si la souris a bougé false sinon
   */
  bool mouseMove() const;
  /**
   * \fn bool getMouseButton(Uint8 i) const
   * \brief Renvoie true si le bouton de souris i est enfoncé false sinon
   */
  bool getMouseButton(Uint8 i) const;
  /**
   * \fn bool getMouseButtonRelease(Uint8 i) const
   * \brief Renvoie true si le bouton de souris i est relaché false sinon
   */
  bool getMouseButtonRelease(Uint8 i) const;
  /**
   * \fn int getXRel() const
   * \brief Renvoie le deplacement horizontal de la souris
   */
  int getXRel() const;
  /**
   * \fn int getYRel() const
   * \brief Renvoie le deplacement vertical de la souris
   */
  int getYRel() const;
  /**
   * \fn int getXAbs() const
   * \brief Renvoie la position horizontale de la souris
   */
  int getXAbs() const;
  /**
   * \fn int getYAbs() const
   * \brief Renvoie la position verticale de la souris
   */
  int getYAbs() const;
  /**
   * \fn bool terminer() const
   * \brief Renvoie true si le programme doit se terminer
   */
  bool terminer() const { return m_terminer; } 
  /**
   * \fn std::condition_variable *getConditionClick()
   * \brief Retourne un pointeur vers la condition "clic de souris"
   */
  std::condition_variable *getConditionClick();
  /**
   * \fn std::mutex *m_clickMutex()
   * \brief Retourne un pointeur vers le mutex de la condition click de souris
   */
  std::mutex *getClickMutex();  
  /**
   * \fn bool getPredicateClick()
   * \brief Retourne la variable de prédicat de clic de souris
   */
  bool getPredicateClick();
private:
  /**
   * \var int m_maxY
   * \brief Résolution verticale de l'écran
   */
  int m_maxY;
  /**
   * \var int m_x
   * \brief mouvement horizontal de la souris absolu
   */
  int m_x;
  /**
   * \var int m_y
   * \brief mouvement vertical de la souris absolu
   */
  int m_y;
  /**
   * \var int m_xRel
   * \brief mouvement horizontal de la souris relatif
   */
  int m_xRel;
  /**
   * \var int m_yRel
   * \brief mouvement vertical de la souris relatif
   */
  int m_yRel;
  /**
   * \var bool m_terminer
   * \brief Termine le programme si true
   */
  bool m_terminer;
  /**
   * \var int m_keys[SDL_NUM_SCANCODES]
   * \brief Touches du clavier appuyées à true touches relachées à false 
   */
  bool m_keys[SDL_NUM_SCANCODES];
  /**
   * \var int m_keysRelease[SDL_NUM_SCANCODES]
   * \brief Touches du clavier relachées récemment à true les autres à false 
   */
  bool m_keysRelease[SDL_NUM_SCANCODES];
  /**
   * \var bool m_mouseButtons
   * \brief Boutons de souris appuyés à true les autres à false
   */
  bool m_mouseButtons[8];
  /**
   * \var bool m_mouseButtonsRelease
   * \brief Boutons de souris relachés à true les autres à false
   */
  bool m_mouseButtonsRelease[8];
  /**
   * \var SDL_Event m_evenements
   * \brief Évênements SDL actuels
   */
  SDL_Event m_evenements;
  /**
   * \var std::condition_variable m_clickCond
   * \brief Condition débloquée en cas de clic de souris
   */
  std::condition_variable m_clickCond;
  /**
   * \var std::mutex m_clickMutex
   * \brief Mutex pour de la condition de clic de souris
   */
  mutable std::mutex m_clickMutex;
  /**
   * \var std::atomic<bool> m_predicateClick
   * \brief Prédicat du clic de souris afin d'éviter les réveils parasites
   */
  std::atomic<bool> m_predicateClick;
};
#endif