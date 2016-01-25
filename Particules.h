#ifndef _DEF_PARTICLES_H
#define _DEF_PARTICLES_H
#include "AbstractMesh.h"
/**
 * \file Particules.h
 * \brief Gestion des particules
 * \class Particules
 * \brief Représente un cube (non affiché) contenant des particules
 */
class Particules : public AbstractMesh
{
public:
  Particules(float taille,unsigned int maxParticules,Shader* shad, Texture* texture);
  ~Particules();
  
  virtual void load();
  virtual void draw();
  virtual void updatePositionsParticules();
  bool isDead() { return m_dead; }
protected:
  GLuint m_vboParticules;
  bool m_dead;
  float m_taille;
  unsigned m_maxParticules;
};

#endif
