#ifndef DEF_SHADER
#define DEF_SHADER
/**
 * \file Shader.h
 * \brief Gestion des Shaders (Programmes pour le GPU)
 */


#include "Include_GL_and_GLM.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>


/**
 * \class Shader
 * \brief Classe de gestion de programmes shaders (compilation, édition de liens, contrôle et destruction) 
 */
class Shader
{  
public:
  /**
   * \fn Shader(std::string const & vertexShader, std::string const & fragmentShader)
   * \brief Constructeur à partir d'un fichier vertexShader et d'un fichier fragmentShader
   */
  Shader(std::string const & vertexShader, std::string const & fragmentShader);
  /**
   * \fn Shader(Shader const & shader)
   * \brief Constructeur de copie d'un shader
   */
  Shader(Shader const & shader);
  /**
   * \fn virtual ~Shader()
   * \brief Destructeur
   */
  virtual ~Shader();
  /**
   * \fn void load()
   * \brief Récupération des sources, compilation et édition de liens
   */
  void load();
  /**
   * \fn std::string getVertexShader() const 
   * \brief Retourne le nom du fichier vertexShader
   */
  std::string getVertexShader() const { return m_vert; }
  /**
   * \fn std::string getFragmentShader() const 
   * \brief Retourne le nom du fichier fragmentShader
   */
  std::string getFragmentShader() const { return m_frag; }
  /**
   * \fn void envoyerMat4(std::string const& nom, glm::mat4 const& matrice)
   * \brief Envoyer une matrice 4x4 comme variable Uniform (commune à toutes les instances de ce shader)
   */
  void envoyerMat4(std::string const& nom, glm::mat4 const& matrice);
  /**
   * \fn void begin()
   * \brief Début du rendu : à appeler avant le rendu d'un objet pour utiliser ce shader pour son affichage
   */
  void begin() { glUseProgram(m_programID); }
  /**
   * \fn void end()
   * \brief À appeler après le rendu d'un objet ne plus utiliser ce shader
   */
  void end() { glUseProgram(0); }
  /**
   * \fn bool isProgram()
   * \brief Renvoie true si le programme shader est valide false sinon
   */
  bool isProgram() { if(glIsProgram(m_programID)==GL_TRUE) return true; else return false; }
  /**
   * \fn GLuint getID()
   * \brief Renvoie l'identifiant OpenGL de ce shader
   */
  GLuint getID() { return m_programID; }
  
  
  void loadSimple();
  
private:
  /**
   * \fn GLuint compileShader(std::string fichierSource, GLenum type)
   * \brief Compile un shader de type vertexShader (GL_VERTEX_SHADER) ou fragmentShader (GL_FRAGMENT_SHADER)
   */
  GLuint compileShader(std::string fichierSource, GLenum type);
  /**
   * \fn void libererRessources()
   * \brief Libère les ressources OpenGL de ce shader
   */
  void libererRessources();
  /**
   * \fn void linkProgram()
   * \brief Édition de liens d'un programme shader
   */
  void linkProgram();
  /**
   * \fn GLuint createProgram()
   * \brief Création de l'identifiant du programme shader
   */
  GLuint createProgram();
  /**
   * \var GLuint m_programID
   * \brief Identifiant du programme shader
   */
  GLuint m_programID;
  /**
   * \var GLuint m_vertID
   * \brief Identifiant du vertex shader
   */
  GLuint m_vertID;
  /**
   * \var m_fragID
   * \brief Identifiant du fragment shader
   */
  GLuint m_fragID;
  /**
   * \var m_vert
   * \brief Nom du fichier source du vertex shader
   */
  std::string m_vert;
  /**
   * \var m_frag
   * \brief Nom du fichier source du fragment shader
   */
  std::string m_frag;
};    
        
#endif
