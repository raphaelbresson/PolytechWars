#ifndef _DEF_SPHERE_H
#define _DEF_SPHERE_H
#include "AbstractMesh.h"
/**
 * \file Sphere.h
 * \brief Implémentation d'une sphère texturée
 * \class Sphere
 * \brief Définition d'une sphère texturée
 */
class Sphere : public AbstractMesh
{
public:
  /**
   * \fn Sphere(float radius, unsigned int nbLat,unsigned int nbLong,Shader *shad, Texture *tex)
   * \brief Constructeur
   */
  Sphere(float radius, unsigned int nbLat,unsigned int nbLong,Shader *shad, Texture *tex);
  /**
   * \fn ~Sphere()
   * \brief Destructeur
   */
  ~Sphere();
  /**
   * \fn void load()
   * \brief Charger les objets GL
   */
  void load();
  /**
   * \fn void initSphere(double r, unsigned int lats, unsigned int longs)
   * \brief Initialisation des vertices et des coordonnées de texture
   */
  void initSphere(double r, unsigned int lats, unsigned int longs);
  /**
   * \fn void draw(glm::mat4 mvp)
   * \brief Affichage
   */
  void draw(glm::mat4 mvp);
  /**
   * \fn float getRadius() const
   * \brief Retourne la valeur du rayon de la sphere
   */
  float getRadius() const { return m_radius; }
private:
  /**
   * \fn void computeIndexes(unsigned int lats, unsigned int longs)
   * \brief Création des indices
   */
  void computeIndexes(unsigned int lats, unsigned int longs);
  /**
   * \var float m_radius
   * \brief Rayon de la sphère
   */
  float m_radius;
  /**
   * \var unsigned int m_lats
   * \brief Précision sur la latitude
   */
  unsigned int m_lats;
  /**
   * \var unsigned int m_longs
   * \brief Precesion sur la longitude
   */
  unsigned int m_longs;
  /**
   * \var std::vector<unsigned short> m_indexes
   * \brief Tableau d'indices
   */
  std::vector<unsigned short> m_indexes;
  /**
   * \var GLuint m_indexesID
   * \brief Identifiant GL du buffer d'indices
   */
  GLuint m_indexesID;
  /**
   * \var GLuint m_vboCoordTextID
   * \brief Identifiant GL du vbo des coordonnées de texture
   */
  GLuint m_vboCoordTextID;
};

#endif
