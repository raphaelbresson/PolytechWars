#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>
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
   * \fn Input()
   * \brief Constructeur
   */
  Input();
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
   * \fn bool terminer() const
   * \brief Renvoie true si le programme doit se terminer
   */
  bool terminer() const { return m_terminer; } 
private:
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
};
#endif