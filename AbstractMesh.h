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
};

#endif
