#ifndef _DEF_MESH_FACTORY_H
#define _DEF_MESH_FACTORY_H
#include "MeshNode.h"
#include "Model3DS.h"
#include "Skybox.h"
#include "Sphere.h"
#include <map>
/**
 * \file MeshFactory.h
 * \brief Construction d'objets 3D et gestion des shaders
 */
/**
 * \def VERTEX_SHADER_3D
 * \brief Nom du vertex shader pour l'affichage 3D
 */
#define VERTEX_SHADER_3D "Shaders/shader3D.vert"
/**
 * \def FRAGMENT_SHADER_3D_TEXTURE_2D
 * \brief Nom du fragment shader pour l'affichage 3D avec une texture 2D
 */
#define FRAGMENT_SHADER_3D_TEXTURE_2D "Shaders/shader3DTexture2D.frag"


/** 
 * \class MeshFactory
 * \brief Classe de gestion des shaders et de génération des modèles 3D
 */
class MeshFactory
{
public:
  /**
   * \fn MeshFactory()
   * \brief Constructeur
   */
  MeshFactory();
  /**
   * \fn ~MeshFactory()
   * \brief Destructeur
   */
  ~MeshFactory();
  /**
   * \fn AbstractMesh* create3DSModel(std::string const& modelName)
   * \brief Création d'un modèle à partir d'un fichier 3DS MAX
   */
  Model3DS* create3DSModel(std::string const& modelName);
  /**
   * \fn Skybox* createSkybox(std::string const& images)
   * \brief Création de l'environnement (simulation de l'espace ici)
   */
  Skybox* createSkybox(std::string const& images);
  /**
   * \fn Sphere* createPlanet(float radius,std::string const& texture)
   * \brief Retourne un sphère texturée qui représente une planète
   */
  Sphere* createPlanet(float radius,std::string const& texture);
protected:
  /**
   * \fn Texture *getTexture(std::string const& name)
   * \brief Retourne directement la texture si elle existe déjà sinon la crée puis la retourne
   */
  Texture *getTexture(std::string const& name);
  
  /**
   * \var Shader * m_shaderTexture2D
   * \brief Programme shader pour les modèles utilisant des textures 2D
   */
  Shader * m_shaderTexture2D;
  /**
   * \var std::map<std::string,Texture*> m_textures
   * \brief Textures gérées directement par la factory (tous sauf 3DS)
   */  
  std::map<std::string,Texture*> m_textures;
};

#endif
