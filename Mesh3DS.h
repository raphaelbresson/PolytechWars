#ifndef _DEF_MESH_3DS_H
#define _DEF_MESH_3DS_H

#include "AbstractMesh.h"

#include <lib3ds/file.h>
#include <lib3ds/node.h>
#include <lib3ds/mesh.h>
#include <lib3ds/vector.h>
#include <lib3ds/matrix.h>
#include <lib3ds/material.h>

/**
 * \file Mesh3DS.h
 * \brief Définition d'un mesh d'un modèle 3DS
 * \class Mesh3DS
 * \brief Mesh d'un modèle 3DS
 */
class Mesh3DS : public AbstractMesh
{
public:
  /**
   * \fn Mesh3DS()
   * \brief Constructeur
   */
  Mesh3DS();
  /**
   * \fn ~Mesh3DS()
   * \brief Destructeur
   */
  ~Mesh3DS();
  /**
   * \fn bool extract(Lib3dsFile *file3DS,Lib3dsMesh *mesh)
   * \brief Extraction d'un mesh 3DS
   */
  bool extract(Lib3dsFile *file3DS,Lib3dsMesh *mesh);
  /**
   * \fn void extractPoints(Lib3dsMesh* mesh, Lib3dsFace* face)
   * \brief Extraction des vertices et coordonnées de texture
   */
  void extractPoints(Lib3dsMesh* mesh, Lib3dsFace* face);
  /**
   * \fn virtual void load()
   * \brief Chargement des objets OpenGL
   */
  virtual void load();
  /**
   * \fn void draw()
   * \brief Affichage
   */
  void draw();
  /**
   * \fn virtual void draw()
   * \brief ne fait rien
   */
  virtual void draw(glm::mat4 mvp) {}
protected:
  
};

#endif