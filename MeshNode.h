#ifndef _DEF_MESH_NODE_H_
#define _DEF_MESH_NODE_H_

#include "AbstractMesh.h"
#include "Sphere.h"

/**
 * \file MeshNode.h
 * \brief Définition de la classe de gestion de modèles 3D
 * \enum NodeType
 * \brief Type de gestion de collisions: NODE_BB -> boundingBox, NODE_SPHERE -> sphere, NODE_SKYBOX -> rien du tout
 */
enum NodeType { NODE_BB = 0, NODE_SPHERE, NODE_SKYBOX };
/**
 * \class MeshNode
 * \brief Classe de gestion de modèles 3D
 */
class MeshNode
{
public:
  /**
   * \fn MeshNode(NodeType type,AbstractMesh* mesh, glm::vec3 position, glm::vec3 orientation  = glm::vec3(0,0,0))
   * \brief Constructeur
   */
  MeshNode(NodeType type,AbstractMesh* mesh, glm::vec3 position,glm::vec3 orientation  = glm::vec3(0,0,0));
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
  /**
   * \fn glm::vec3 getMinBB() const
   * \brief Retourne la position du MeshNode
   */
  glm::vec3 getMinBB() const { return m_minBB; }
  /**
   * \fn glm::vec3 getMaxBB() const
   * \brief retourne l'orientation du MeshNode
   */
  glm::vec3 getMaxBB() const { return m_maxBB; } 
  /**
   * \fn void updateBoundingBox();
   * \brief Recalcule la boundingBox
   */
  void updateBoundingBox();
  /**
   * \fn float testCollision(MeshNode *other)
   * \brief Retourne la distance entre les deux objets. Si la distance est négative il y a collision et la distance retournée représente "l'enfoncement" d'un objet dans l'autre
   */
  float testCollision(MeshNode *other); 
  /**
   * \fn float collisionBoundingBox(MeshNode* other)
   * \brief test de collision pour deux BoundingBox entre elles
   */
   float collisionBoundingBox(MeshNode* other);  
  /**
   * \fn float collisionSphereBoundingBox(MeshNode *sphere,MeshNode* bb)
   * \brief test de collision pour une BoundingBox et une sphère
   */
  float collisionSphereBoundingBox(MeshNode *sphere,MeshNode* bb);
  /**
   * \fn float collisionSphere(MeshNode* other)
   * \brief test de collision pour deux sphères entre-elles
   */
  float collisionSphere(MeshNode* other);
private:
  /**
   * \var NodeType
   * \brief Type de node (pour les collisions)
   */
  NodeType m_type;
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
  /**
   * \var m_minBB
   * \brief Position minimale de la bounding box
   */
  glm::vec3 m_minBB;
  /**
   * \var m_maxBB
   * \brief m_maxBB
   */
  glm::vec3 m_maxBB;
  
  
};

#endif
 
