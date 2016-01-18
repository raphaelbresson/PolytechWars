#ifndef _DEF_SOUND_MANAGER_H
#define _DEF_SOUND_MANAGER_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <SDL2/SDL_mixer.h>
/**
 * \file SoundManager.h
 * \brief Définition du gestionnaire de sons
 * \class SoundManager
 * \brief Gestionnaire de sons
 */
class SoundManager
{
public:
  /**
   * \fn SoundManager()
   * \brief Constructeur
   */
  SoundManager();
  /**
   * \fn ~SoundManager()
   * \brief Constructeur
   */
  ~SoundManager();
  /**
   * \fn void addMusic(std::string const& file)
   * \brief Ajoute une musique à la liste de lecture
   */
  void addMusic(std::string const& file);
  /**
   * \fn void addEffect(std::string const& name, std::string const& file)
   * \brief Ajoute un effet à la liste des effets
   */
  void addEffect(std::string const& name, std::string const& file);
  /**
   * \fn bool isPlayingMusic()
   * \brief Renvoie true si le gectionnaire de son est en train de jouer une musique false sinon
   */
  bool isPlayingMusic();
  /**
   * \fn playMusic()
   * \brief Lit la liste de lecture
   */
  void playMusic();
  /**
   * \fn void nextMusic()
   * \brief Lit la musique suivant dans la liste de lecture
   */
  void nextMusic();
  /**
   * \fn void playEffect(std::string const& name,int volume)
   * \brief Joue l'effet identifié par son nom
   */
  void playEffect(std::string const& name,int volume);
private:
  /**
   * \var std::vector<Mix_Music*> m_musiques
   * \brief Liste de lecture des musiques
   */
  std::vector<Mix_Music*> m_musiques;
  /**
   * \var std::map<std::string,Mix_Chunk*> m_effects
   * \brief Conteneur des effets identifiés par leur nom
   */
  std::map<std::string,Mix_Chunk*> m_effects;
  /**
   * \var std::map<std::string,unsigned int> m_effects
   * \brief Conteneur des canaux des effets identifiés par leur nom
   */
  std::map<std::string,int> m_chanelEffects;
  /**
   * \var unsigned int m_currentMusic
   * \brief Indice de la musique courante
   */
  unsigned int m_currentMusic;
};

#endif