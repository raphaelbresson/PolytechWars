#ifndef _DEF_MODEL_3DS_H
#define _DEF_MODEL_3DS_H
#include "Mesh3DS.h"
/**
 * \file Model3DS.h
 * \brief Importation d'un modèle 3D depuis le format 3DS MAX (sans les animations)
 * \class Model3DS
 * \brief Gestion des modèle 3DS
 */
class Model3DS : public AbstractMesh
{
public:
  /**
   * \fn Model3DS(std::string const& file_3ds, Shader* shader)
   * \brief Constructeur à partir du fichier 3ds et d'un shader
   */
  Model3DS(std::string const& file_3ds, Shader* shader);
  /**
   * \fn virtual ~Model3DS()
   * \brief Destructeur
   */
  virtual ~Model3DS();
  /**
   * \fn virtual void load()
   * \brief 
   */
  virtual void load();
  /**
   * \fn virtual void draw(glm::mat4 mvp)
   * \brief Affichage
   */
  virtual void draw(glm::mat4 mvp);
private:
  /**
   * \var std::string m_fileName
   * \brief Nom du fichier 3DS
   */
  std::string m_fileName;
  /**
   * \var std::vector<Mesh3DS*> m_meshes
   * \brief Tableau de Mesh3DSs que contient ce modèle
   */
  std::vector<Mesh3DS*> m_meshes;
};

#endif