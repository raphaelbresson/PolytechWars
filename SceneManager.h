#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <iostream>
#include <vector>
#include <string>

#include "CameraFPS.h"
#include "CameraFlightSimulator.h"
#include "Input.h"
#include "MeshFactory.h"
#include "GuiFactory.h"
#include "SoundManager.h"

/**
 * \file SceneManager.h
 * \author Raphaël BRESSON, Mahdi HAMMOUCHE
 * \brief Gestion des modèles et de l'affichage
 * \def FPS_LIMIT
 * \brief Limitation de la fréquence de rafraichissement à 60 FPS
 */
#define FPS_LIMIT 60
/**
 * \class SceneManager
 * \brief Gestionnaire des modèle, des caméras (pour le 3D) et de l'affichage
 */
class SceneManager 
{
public:
 /**
  * \fn SceneManager()
  * \brief Constucteur
  */
  SceneManager();
 /**
  * \fn ~SceneManager()
  * \brief Constucteur
  */
  virtual ~SceneManager();
 /**
  * \fn MeshNode* addMeshNode(NodeType type,Mesh* mesh, glm::vec3 position, glm::vec3 orientation = glm::vec3(0,0,0))
  * \brief Ajout d'un modèle 3D dans la scene, renvoie le MeshNode créé
  */
  MeshNode* addMeshNode(NodeType type,AbstractMesh* mesh, glm::vec3 const& position, glm::vec3 const& orientation = glm::vec3(0,0,0));
 /**
  * \fn void addWidget(Widget* wid)
  * \brief Ajout d'un modèle 2D sur l'écran
  */
  void addWidget(AbstractWidget* wid);
 /**
  * \fn void init3D(int w, int h)
  * \brief Initialisation des modèles 3D et de la caméra
  */
  void init3D(int w, int h);
 /**
  * \fn void init2D()
  * \brief Initialisation des objets 2D et de la matrice orthogonale
  */
  void init2D();
  /**
   * \fn void initSounds();
   * \brief Initialisation des musiques et des effets sonores
   */
  void initSounds();
 /**
  * \fn void drawAll()
  * \brief Affichage de tous les modèles
  */
  void drawAll();
  /**
  * \fn void onPreRender()
  * \brief Avant le rendu
  */
  void onPreRender();
  /**
   * \fn void testsCollision()
   * \brief Tests de collision des m_meshDynNodes
   */
  void testsCollision();
 /**
  * \fn bool execute(SDL_Window* window, unsigned int w, unsigned int h)
  * \brief Exécution de la boucle principale
  */
  bool execute(SDL_Window* window, unsigned int w, unsigned int h);
 /**
  * \fn void updateCameras()
  * \brief Déplace les caméras et met à jour les matrices
  */
 void updateCameras();
  /**
  * \fn void changeCamera()
  * \brief Change de caméra active
  */
 void changeCamera();
private:
 /**
  * \var std::vector<MeshNode*> m_meshNodes
  * \brief Tableau d'objets 3D
  */ 
  std::vector<MeshNode*> m_meshNodes;
  /**
  * \var std::vector<MeshNode*> m_meshDynNodes
  * \brief Tableau d'objets 3D déplaçables (à tester pour les collisions)
  */ 
  std::vector<MeshNode*> m_meshDynNodes;
 /**
  * \var std::vector<AbstractWidget*> m_widgets
  * \brief Tableau d'objets 2D
  */ 
  std::vector<AbstractWidget*> m_widgets;
 /**
  * \var std::vector<AbstractCamera*> m_cameras
  * \brief Différentes caméra
  */ 
  std::vector<AbstractCamera*> m_cameras;
 /**
  * \var unsigned int m_activeCamera
  * \brief Indice de la camera active
  */
  unsigned int m_activeCamera;
 /**
  * \var Input m_input 
  * \brief Ecouteur d'évênements clavier
  */ 
  Input m_input;
 /**
  * \var glm::mat4 m_ortho
  * \brief Matrice de projection orthogonale (pour le 2D)
  */ 
  glm::mat4 m_ortho;
  /**
   * \var GuiFactory m_guiFact
   * \brief Constructeur d'objets 2D
   */
  GuiFactory m_guiFact;
  /**
   * \var MeshFactory m_meshFact 
   * \brief Constructeur d'objets 3D
   */
  MeshFactory m_meshFact;
  /**
   * \var SoundManager m_soundMgr
   * \brief Gère l'audio
   */
  SoundManager m_soundMgr;
};

#endif