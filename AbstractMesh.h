#ifndef _DEF_ABSTRACT_MESH_H
#define _DEF_ABSTRACT_MESH_H
#include "AbstractGraphicObject.h"
#include "Texture.h"

/**
 * \file AbstractMesh.h
 * \brief Définition d'un type polymorphe pour les modèles 3D
 * \class AbstractMesh
 * \brief Type polymorphe pour les modèles 3D
 */

class AbstractMesh : public AbstractGraphicObject
{
public:
  /**
   * \fn AbstractMesh(Shader *shader, Texture* texture)
   * \brief Constructeur à partir de la texture donnés en argument
   */
  AbstractMesh(Shader *shader, Texture* texture);
  /**
   * \fn AbstractMesh(AbstractMesh* mesh)
   * \brief Constructeur de copie
   */
  AbstractMesh(AbstractMesh* mesh);
  /**
   * \fn virtual ~Mesh();
   * \brief Destructeur
   */
  virtual ~AbstractMesh();
  /**
   * \fn virtual void load()
   * \brief Construit les objets OpenGL (vbo et vao) pour ce modèle
   */
  virtual void load();
  /**
   * \fn void draw(glm::mat4 mvp)
   * \brief Méthode virtuelle pure qui affiche le mesh en fonction de la matrice de modelviewProjection
   */
  virtual void draw(glm::mat4 mvp) = 0;
  /**
   * \fn virtual void cleanUp()
   * \brief Détruit les objets de construction intermédiaires
   */
  virtual void cleanUp();
  
  /**
   * \fn glm::vec3 getMaxVert() const
   * \brief Retourne les coordonnées maximales de la boundingBox
   */
  glm::vec3 getMaxVert() const { return m_maxVert; }
  
  /**
   * \fn glm::vec3 getMaxVert() const
   * \brief Retourne les coordonnées minimales de la boundingBox
   */
  glm::vec3 getMinVert() const { return m_minVert; }
  /**
   * \fn void initBoundingBox(glm::vec3 const & vertex)
   * \brief Teste les coordonnées de l'objet et construit la boundingBox (m_min,m_max)
   */
  void updateBoundingBox(float x, float y, float z);
protected:
  /**
   * \var std::vector<float> m_coordTex;
   * \brief Tableau de coordonnées de textures
   */
  std::vector<float> m_coordTex;
  /**
   * \var Texture m_texture
   * \brief Texture de l'objet
   */
  Texture *m_texture;
  /**
   * \var unsigned long m_nbVertices
   * \brief Nombre de vertices de ce mesh
   */
  unsigned long m_nbVertices;
  /**
   * \var glm::m_minVert
   * \brief Coordonnées minimales (bounding box)
   */
  glm::vec3 m_minVert;
  /**
   * \var glm::vec3 m_maxVert
   * \brief Coordonnées maximales (bounding box)
   */
  glm::vec3 m_maxVert;
  
  
};

#endif
