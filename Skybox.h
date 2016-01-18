#ifndef _DEF_SKYBOX_H
#define _DEF_SKYBOX_H
#include "AbstractMesh.h"
/**
 * \file Skybox.h
 * \brief Simulation d'environnement via skybox monotexturée
 * \class Skybox
 * \brief Cube avec textures de ciel plaquées
 */
class Skybox : public AbstractMesh
{
public:
  /**
   * \fn Skybox(float taille,Shader* shad, Texture* tex)
   * \brief Constructeur pour une skybox mono-texturée
   */
  Skybox(float taille,Shader* shad, Texture* tex);
  /**
   * \fn virtual ~Skybox()
   * \brief Destructeur
   */
  virtual ~Skybox();
  /**
   * \fn virtual void draw(glm::mat4 mvp)
   * \brief Affichage	
   */
  virtual void draw(glm::mat4 mvp);
  
private:
};

#endif