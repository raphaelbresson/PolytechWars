#ifndef _DEF_ABSTRACT_GRAPHIC_OBJECT_H_ 
#define _DEF_ABSTRACT_GRAPHIC_OBJECT_H_
#include <iostream>
#include <vector>
#include "Include_GL_and_GLM.h"
#include "Shader.h"
/**
 * \file AbstractGraphicObject.h
 * \author Raphaël BRESSON, Mahdi HAMMOUCHE
 * \brief Définit un type polymorphe pour les objets graphiques
 * \def BUFFER_OFFSET(offset)
 * \brief Macro de conversion d'un entier non signé en adresse (utile lors de l'initialisation des vao)
 */
#define BUFFER_OFFSET(offset) ((void*)(offset))
/**
 * \class AbstractGraphicObject
 * \brief Classe abstraite définissant un type polymorphe pour les objets graphiques
 */
class AbstractGraphicObject
{
public:
  /**
   * \fn AbstractGraphicObject(Shader* shad)
   * \brief Construit un objet graphique en utilisant le shader donné en argument pour le rendu.
   */
  AbstractGraphicObject(Shader* shad) : m_vboID(0), m_vaoID(0), m_shader(shad) {}
  
  /**
   * \fn virtual ~AbstractGraphicObject()
   * \brief Destructeur
   */
  virtual ~AbstractGraphicObject()
  { 
    cleanUp(); 
    if(glIsBuffer(m_vboID) == GL_TRUE)
      glDeleteBuffers(1,&m_vboID);
    if(glIsVertexArray(m_vaoID) == GL_TRUE)
      glDeleteVertexArrays(1,&m_vboID);
  }
  
  /**
   * \fn virtual void load()
   * \brief Génère les objets opengl (vbo,vao,textures) pour cet objet graphique
   */
  virtual void load() = 0;
  /**
   * \fn virtual void cleanUp()
   * \brief Détruit les objets de construction intermédiaires
   */
  virtual void cleanUp() { m_vertices.clear(); }
protected:
  /**
   * \var GLuint m_vboID
   * \brief Identifiant OpenGL du Vertex Buffer Object (VBO) (généré lors de l'appel de load())
   */
  GLuint m_vboID;
  /**
   * \var GLuint m_vaoID
   * \brief Identifiant OpenGL du Vertex Array Object (VAO) (généré lors de l'appel de load())
   */
  GLuint m_vaoID;
  /**
   * \var Shader m_shader
   * \brief Shader pour le rendu (les shaders sont gérés en externe par les classes GuiFactory -> 2D ou SceneFactory -> 3D )
   */
  Shader *m_shader;
  /**
   * \var std::vector<float> m_vertices
   * \brief Tableau temporaire de sommets
   */
  std::vector<float> m_vertices;
};

#endif
