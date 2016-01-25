#include "Particules.h"

Particules::Particules(float taille,unsigned int maxParticules,Shader* shad, Texture* texture) :
  AbstractMesh(shad,texture), m_vboParticules(0), m_dead(0),m_taille(taille), m_maxParticules(maxParticules)
{
  
}

Particules::~Particules()
{
  if(glIsBuffer(m_vboParticules) == GL_TRUE)
    glDeleteBuffers(1,&m_vboParticules);
}

void Particules::load()
{
  m_vertices = {
   -m_taille,-m_taille, 0.0f,       m_taille,-m_taille, 0.0f,
   -m_taille, m_taille, 0.0f,       m_taille, m_taille, 0.0f
  };
  
}

void Particules::draw()
{
  
}

void Particules::updatePositionsParticules()
{
  
}
