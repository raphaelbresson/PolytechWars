#ifndef TEXTURE_H
#define TEXTURE_H

#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Include_GL_and_GLM.h"

#include <iostream>
#include <vector>

/**
 * \file Texture.h
 * \author Raphaël BRESSON, Mehdi HAMMOUCHE 
 * \brief Gestion des textures
 * \class Texture
 * \brief Gère les textures OpenGL et leur importation via une image ou une police
 */
class Texture
{
public:
  /**
   * \fn Texture()
   * \brief Contruit une texture vide
   */
  Texture();
  /**
   * \fn Texture(std::string const& fn)
   * \brief Construit une texture à partir d'une image
   */
  Texture(std::string const& fn);
  /**
   * \fn Texture(Texture &tex)
   * \brief Constructeur de copie
   */
  Texture(Texture & tex);
  /**
   * \fn ~Texture()
   * \brief Destructeur
   */
  ~Texture();
  /**
   * \fn void load()
   * \brief Création des objets GL pour une texture image
   */
  void load();
  /**
   * \fn void loadCullFace()
   * \brief Création des objets GL pour une texture image sans répétition
   */
  void loadCullFace();
  /**
   * \fn void loadCubemap(std::vector<std::string> faces)
   * \brief Création des objets GL pour une texture Cube Map
   */
  void loadCubemap(std::vector<std::string> faces);
  /**
   * \fn void loadEmpty(unsigned int width, unsigned int height, GLenum format, GLenum formatInterne)
   * \brief Création des objets GL pour une texture vide
   */
  void loadEmpty(unsigned int width, unsigned int height, GLenum format, GLenum formatInterne);
  /**
   * \fn Texture & operator = (Texture & tex)
   * \brief Equivalent au constructeur de copie
   */
  Texture & operator = (Texture & tex);
  /**
   * \fn void bind()
   * \brief Verrouillage de la texture (obligatoire pour pouvoir afficher ou modifier les objets GL)
   */
  void bind();
  /**
   * \fn void unbind()
   * \brief Verrouillage de la texture (Facultatif)
   */
  void unbind();
  /**
   * \fn void getName()
   * \brief Renvoie le nom du fichier image ou police
   */
  std::string getName();
  /**
   * \fn void getID()
   * \brief Renvoie l'identifiant OpenGL de la texture
   */
  GLuint getID() { return m_id; }
  /**
   * \fn bool isValid()
   * \brief Renvoie true si la police est valide false sinon
   */
  bool isValid() 
  { 
    if(glIsTexture(m_id)==GL_TRUE)
	return true;
    return false;
  }
protected:
  /**
   * \fn SDL_Surface* readPixels()
   * \brief Retourne une SDL_Surface à parir de l'image désignée par m_fn
   */
  SDL_Surface* readPixels();
  /**
   * \fn SDL_Surface* readPixels(std::string const& image)
   * \brief Retourne une SDL_Surface à parir de l'image donnée en argument
   */
  SDL_Surface* readPixels(std::string image);
  /**
   * \fn SDL_Surface* inversePixels(SDL_Surface *imageSource)
   * \brief Inverse les pixels pour retourner une image
   */
  SDL_Surface* inversePixels(SDL_Surface *imageSource);
  /**
   * \fn void uploadToGPU(SDL_Surface *image)
   * \brief Charge les objets OpenGL pour cette texture
   */
  void uploadToGPU(SDL_Surface *image);
  /**
   * \fn void detectFormat(SDL_Surface* image,GLenum & formatInterne, GLenum & format);
   * \brief Détecte le format et le format interne d'une image
   */
  void detectFormat(SDL_Surface* image,GLenum & formatInterne, GLenum & format);
  
  /**
   * \var GLuint m_id
   * \brief Identifiant OpenGL pour cette texture
   */
  GLuint m_id;
  /**
   * \var std::string m_fn
   * \brief Nom du fichier image de cette texture
   */
  std::string m_fn;
  /**
   * \var GLenum m_format
   * \brief Format de l'image
   */
  GLenum m_format;
};

#endif