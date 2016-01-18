#ifndef _DEF_MESH_NODE_H_
#define _DEF_MESH_NODE_H_

#include "AbstractMesh.h"

/**
 * \file MeshNode.h
 * \brief Définition de la classe de gestion de modèles 3D
 * \class MeshNode
 * \brief Classe de gestion de modèles 3D
 */
class MeshNode
{
public:
  /**
   * \fn MeshNode(AbstractMesh* mesh, glm::vec3 position, glm::vec3 orientation  = glm::vec3(0,0,0))
   * \brief Constructeur
   */
  MeshNode(AbstractMesh* mesh, glm::vec3 position, glm::vec3 orientation  = glm::vec3(0,0,0));
  /**
   * \fn ~MeshNode()
   * \brief Constructeur
   */
  ~MeshNode();
  /**
   * \fn void setPosition(glm::vec3 const& position)
   * \brief Changement de position
   */
  void setPosition(glm::vec3 const& position);
  /**
   * \fn void setOrientation(glm::vec3 const& orientation)
   * \brief Changement d'orientation
   */
  void setOrientation(glm::vec3 const& orientation);
  /**
   * \fn void setRotationMatrix(glm::mat4 const& rotMat)
   * \brief Changement de la matrice de rotation
   */
  void setRotationMatrix(glm::mat4 const& rotMat);
  /**
   * \fn void draw(glm::mat4 const& projection, glm::mat4 const& modelview)
   * \brief Affiche le modèle 3D associé
   */
  void draw(glm::mat4 const& projection, glm::mat4 const& modelview);
  /**
   * \fn glm::vec3 getPosition() const
   * \brief Retourne la position du MeshNode
   */
  glm::vec3 getPosition() const { return m_position; }
  /**
   * \fn glm::vec3 getOrientation()
   * \brief retourne l'orientation du MeshNode
   */
  glm::vec3 getOrientation() const { return m_orientation; }
  
private:
  /**
   * \var AbstractMesh* m_mesh
   * \brief Modèle 3D associé
   */
  AbstractMesh* m_mesh;
  /**
   * \var glm::vec3 m_position
   * \brief Position du node
   */
  glm::vec3 m_position;
  /**
   * \var glm::vec3 m_orientation
   * \brief Orientation de node
   */
  glm::vec3 m_orientation;
  /**
   * \var glm::mat4 m_rotationMatrix
   * \brief Matrice de rotation du MeshNode
   */
  glm::mat4 m_rotationMatrix;
};

#endif
 
